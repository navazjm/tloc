#include "app.h"
#include "language.h"
#include "options.h"
#include "utils.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void tloc_app_init(TLOC_App* app) {
    app->version = "0.1.0";
    tloc_options_init(&app->opts);

    app->file_summaries = NULL;
    app->file_summaries_buffer_size = 32;
    app->file_summaries_count = 0;
}

/* Destroy base application, freeing up memory allocations */
void tloc_app_destroy(TLOC_App* app) {
    if (app) {
        tloc_options_destory(&app->opts);
        if (app->file_summaries) {
            free(app->file_summaries);
        }
    }
}

/* Parse command line arguments (options), setting base application options
 * Usage Formats:
 *  tloc [...options]
 *  tloc path [...options]
 */
void tloc_app_parse_cmd_args(TLOC_App* app, int argc, char** argv) {
    // early return as we already set default values in app initializer
    if (argc == 1)
        return;

    if (strcmp(argv[1], tloc_args[0].shorthand) == 0 || strcmp(argv[1], tloc_args[0].longhand) == 0) {
        tloc_options_args_print_help();
        tloc_app_destroy(app);
        exit(EXIT_SUCCESS);
    }
    if (strcmp(argv[1], tloc_args[1].shorthand) == 0 || strcmp(argv[1], tloc_args[1].longhand) == 0) {
        printf("tloc v%s\n", app->version);
        tloc_app_destroy(app);
        exit(EXIT_SUCCESS);
    }
    if (strcmp(argv[1], tloc_args[2].shorthand) == 0 || strcmp(argv[1], tloc_args[2].longhand) == 0) {
        tloc_language_print_supported_languages();
        tloc_app_destroy(app);
        exit(EXIT_SUCCESS);
    }

    // set file path to second command line arg, if path exists and we have access to it
    uint8_t args_stating_index = 1;
    if (access(argv[1], F_OK) == 0) {
        app->opts.path = strdup(argv[1]);
        args_stating_index = 2;
    }

    char* options[2] = {NULL, NULL};
    for (uint8_t i = args_stating_index; i < argc; i++) {
        tloc_utils_split_cmd_arg(argv[i], options);
        bool found_valid_option = tloc_options_map_arg(&app->opts, options[0], options[1]);

        free(options[0]);
        if (options[1]) {
            free(options[1]);
        }
        options[0] = options[1] = NULL;
        if (!found_valid_option) {
            printf("Error! Invalid command line arg: %s\n", argv[i]);
            tloc_app_destroy(app);
            exit(EXIT_FAILURE);
        }
    }
}

/* Begins the process of parsing app->file_path */
void tloc_app_count_lines_of_code(TLOC_App* app) {
    struct stat path_stat;
    if (stat(app->opts.path, &path_stat) != 0) {
        printf("Error! Unable to reslove path: %s\n", app->opts.path);
        tloc_app_destroy(app);
        exit(EXIT_FAILURE);
    }

    if (S_ISREG(path_stat.st_mode)) { // app->path is a single file
        app->file_summaries = (TLOC_File_Summary*)malloc(sizeof(TLOC_File_Summary));
        if (app->file_summaries == NULL) {
            printf("Error! Failed to allocate memory to track file information\n");
            tloc_app_destroy(app);
            exit(EXIT_FAILURE);
        }
        tloc_app_count_lines_of_code_file(app, app->opts.path);
    } else if (S_ISDIR(path_stat.st_mode)) {
        app->file_summaries = (TLOC_File_Summary*)malloc(app->file_summaries_buffer_size * sizeof(TLOC_File_Summary));
        if (app->file_summaries == NULL) {
            printf("Error! Failed to allocate memory to track file information\n");
            tloc_app_destroy(app);
            exit(EXIT_FAILURE);
        }
        tloc_app_count_lines_of_code_dir(app);
    } else {
        printf("Error! %s is neither a regular file nor a directory.\n", app->opts.path);
        tloc_app_destroy(app);
        exit(EXIT_FAILURE);
    }
}

/* Parses a specific file, calculating total lines, blank lines, comment lines, and code lines */
void tloc_app_count_lines_of_code_file(TLOC_App* app, const char* file_path) {
    if (app->file_summaries_count == app->file_summaries_buffer_size) {
        app->file_summaries_buffer_size *= 2;
        TLOC_File_Summary* temp =
            realloc(app->file_summaries, app->file_summaries_buffer_size * sizeof(TLOC_File_Summary));
        if (temp == NULL) {
            printf("Error! Failed to reallocate memory to track file information\n");
            tloc_app_destroy(app);
            exit(EXIT_FAILURE);
        }
        app->file_summaries = temp;
    }

    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(file_path, "r");
    if (fp == NULL) {
        return;
    }

    TLOC_File_Summary file_summary = {strdup(file_path), NULL, 0, 0, 0, 0};
    char* dot = strrchr(file_path, '.');
    file_summary.ext = dot ? strdup(dot + 1) : NULL;
    const TLOC_Language* found_supported_language = tloc_language_get_by_extension(file_summary.ext);
    if (found_supported_language == NULL && app->opts.exclude_unsupported) {
        return;
    }
    uint8_t found_starting_multiline_comment = 0;

    while ((read = getline(&line, &len, fp)) != -1) {
        file_summary.total_lines++;
        if (found_supported_language == NULL) {
            continue;
        }
        char* line_trimmed = tloc_utils_string_trim_whitespace(line);
        if (strlen(line_trimmed) == 0 || *line_trimmed == '\n' || strcmp(line_trimmed, "\r\n") == 0) {
            file_summary.blank_lines++;
            continue;
        }
        if (strncmp(found_supported_language->multiline_comment_start, line_trimmed,
                    strlen(found_supported_language->multiline_comment_start)) == 0) {
            file_summary.comment_lines++;
            found_starting_multiline_comment = 1;
            if (tloc_utils_string_ends_with(line_trimmed, found_supported_language->multiline_comment_end)) {
                found_starting_multiline_comment = 0;
            }
            continue;
        }
        if (found_starting_multiline_comment) {
            if (tloc_utils_string_ends_with(line_trimmed, found_supported_language->multiline_comment_end)) {
                found_starting_multiline_comment = 0;
            }
            file_summary.comment_lines++;
            continue;
        }
        if (found_supported_language->singleline_comment &&
            strncmp(found_supported_language->singleline_comment, line_trimmed,
                    strlen(found_supported_language->singleline_comment)) == 0) {
            file_summary.comment_lines++;
            continue;
        }
        file_summary.code_lines++;
    }

    app->file_summaries[app->file_summaries_count++] = file_summary;

    fclose(fp);
    if (line)
        free(line);
}

/* Parses a directory of files */
void tloc_app_count_lines_of_code_dir(TLOC_App* app) {
    if (app->opts.use_git) {
        tloc_app_count_lines_of_code_dir_git(app);
        return;
    }
    tloc_app_count_lines_of_code_dir_recursion(app, app->opts.path);
}

/*
 * Get files returned from command 'git ls-files app->path'
 * For each file, call tloc_count_lines_of_code_file
 */
void tloc_app_count_lines_of_code_dir_git(TLOC_App* app) {
    char* git_cmd;
    asprintf(&git_cmd, "git ls-files %s", app->opts.path);

    FILE* git_cmd_fp;
    git_cmd_fp = popen(git_cmd, "r");
    if (git_cmd_fp == NULL) {
        printf("Failed to run 'git ls-files' cmd. Defaulting to all files\n");
        tloc_app_destroy(app);
        free(git_cmd);
        exit(EXIT_FAILURE);
    }

    char* git_cmd_file_line = NULL;
    size_t git_cmd_file_len = 0;
    ssize_t git_cmd_file_read;

    while ((git_cmd_file_read = getline(&git_cmd_file_line, &git_cmd_file_len, git_cmd_fp)) != -1) {
        git_cmd_file_line[strcspn(git_cmd_file_line, "\n")] = 0;
        tloc_app_count_lines_of_code_file(app, git_cmd_file_line);
    }

    pclose(git_cmd_fp);
    if (git_cmd_file_line) {
        free(git_cmd_file_line);
    }
}

/* Starting at app->path, navigate inside all subdirs and parse each file by calling tloc_count_lines_of_code_file */
void tloc_app_count_lines_of_code_dir_recursion(TLOC_App* app, const char* dir_path) {
    struct dirent* entry;
    struct stat entry_info;
    DIR* dir = opendir(dir_path);

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char* full_path;
        if (dir_path[strlen(dir_path) - 1] != '/') {
            asprintf(&full_path, "%s/%s", dir_path, entry->d_name);
        } else {
            asprintf(&full_path, "%s%s", dir_path, entry->d_name);
        }

        if (stat(full_path, &entry_info) != 0) {
            continue;
        }

        if (S_ISDIR(entry_info.st_mode)) {
            tloc_app_count_lines_of_code_dir_recursion(app, full_path);
        } else if (S_ISREG(entry_info.st_mode)) {
            tloc_app_count_lines_of_code_file(app, full_path);
        }
    }

    closedir(dir);
    if (entry) {
        free(entry);
    }
}

/* Begin the process of displaying file summaries to the user */
void tloc_app_display_results(TLOC_App* app) {
    if (app->file_summaries == NULL || app->file_summaries_count == 0) {
        return;
    }

    if (app->opts.group_by_language) {
        tloc_app_display_results_by_language(app);
        return;
    }

    tloc_app_display_results_by_file(app);
}

/* Display file summaries per file */
void tloc_app_display_results_by_file(TLOC_App* app) {
    size_t buffer_size = 1024 + app->file_summaries_count * 256;
    char* output = (char*)malloc(buffer_size);
    if (output == NULL) {
        perror("Failed to allocate memory");
        return;
    }
    output[0] = '\0';

    strcat(output,
           "------------------------------------------------------------------------------------------------\n");
    strcat(output, "File name                                    blank        comment           code          total\n");
    strcat(output,
           "------------------------------------------------------------------------------------------------\n");

    int total_blank = 0, total_comment = 0, total_code = 0, total_lines = 0;
    char* output_line;

    for (int i = 0; i < app->file_summaries_count; i++) {
        TLOC_File_Summary file_summary = app->file_summaries[i];

        // cannot use strdup bc we may have prepend file name with '/' when formatting based on TLOC_PP_Option
        char* temp_file_summary_name = (char*)malloc((strlen(file_summary.name) + 2) * sizeof(char));
        if (temp_file_summary_name == NULL) {
            printf("Failed to allocate memory for formatting file summary name\n");
            tloc_app_destroy(app);
            exit(EXIT_FAILURE);
        }
        strcpy(temp_file_summary_name, file_summary.name);

        tloc_utils_normalize_file_path(temp_file_summary_name);
        tloc_utils_format_file_path_by_pp_option(temp_file_summary_name, app->opts.print_parent);
        int temp_file_summary_name_len = strlen(temp_file_summary_name);
        if (temp_file_summary_name_len > 35) {
            memmove(temp_file_summary_name, temp_file_summary_name + temp_file_summary_name_len - 35, 36);
        }

        asprintf(&output_line, "%-35s %14d %14d %14d %14d\n", temp_file_summary_name, file_summary.blank_lines,
                 file_summary.comment_lines, file_summary.code_lines, file_summary.total_lines);
        strcat(output, output_line);

        total_blank += file_summary.blank_lines;
        total_comment += file_summary.comment_lines;
        total_code += file_summary.code_lines;
        total_lines += file_summary.total_lines;

        free(temp_file_summary_name);
        temp_file_summary_name = NULL;
    }

    if (app->file_summaries_count > 1) {
        strcat(output,
               "------------------------------------------------------------------------------------------------\n");
        asprintf(&output_line, "TOTAL: %43d %14d %14d %14d\n", total_blank, total_comment, total_code, total_lines);
        strcat(output, output_line);
        strcat(output,
               "------------------------------------------------------------------------------------------------\n");
    }

    printf("%s", output);
    free(output);
    free(output_line);
}

/* Group file summaries by supported language name, displaying results by language */
void tloc_app_display_results_by_language(TLOC_App* app) {
    int language_summary_groups_count = 0;
    TLOC_Language_Summary* language_summary_groups = NULL;

    for (int i = 0; i < app->file_summaries_count; i++) {
        TLOC_File_Summary file_summary = app->file_summaries[i];
        const TLOC_Language* supported_language = tloc_language_get_by_extension(file_summary.ext);
        const char* language_name = supported_language ? supported_language->name : "N/A";
        TLOC_Language_Summary* group = tloc_summary_find_or_create_language_summary(
            &language_summary_groups, &language_summary_groups_count, language_name);

        group->total_files++;
        group->total_lines += file_summary.total_lines;
        group->blank_lines += file_summary.blank_lines;
        group->code_lines += file_summary.code_lines;
        group->comment_lines += file_summary.comment_lines;
    }

    size_t buffer_size = 1024 + language_summary_groups_count * 256;
    char* output = (char*)malloc(buffer_size);
    if (output == NULL) {
        perror("Failed to allocate memory");
        return;
    }
    output[0] = '\0';

    strcat(output, "-------------------------------------------------------------------------------------------\n");
    strcat(output, "Language                 files          blank        comment           code      "
                   "    total\n");
    strcat(output, "-------------------------------------------------------------------------------------------\n");

    int total_blank = 0, total_comment = 0, total_code = 0, total_lines = 0, total_files = 0;
    char* output_line;

    for (int i = 0; i < language_summary_groups_count; i++) {
        TLOC_Language_Summary langauge_summary_group = language_summary_groups[i];
        asprintf(&output_line, "%-15s %14d %14d %14d %14d %14d\n", langauge_summary_group.name,
                 langauge_summary_group.total_files, langauge_summary_group.blank_lines,
                 langauge_summary_group.comment_lines, langauge_summary_group.code_lines,
                 langauge_summary_group.total_lines);
        strcat(output, output_line);

        total_blank += langauge_summary_group.blank_lines;
        total_comment += langauge_summary_group.comment_lines;
        total_code += langauge_summary_group.code_lines;
        total_lines += langauge_summary_group.total_lines;
        total_files += langauge_summary_group.total_files;
    }

    if (language_summary_groups_count > 1) {
        strcat(output, "-------------------------------------------------------------------------------------------\n");
        asprintf(&output_line, "TOTAL: %23d %14d %14d %14d %14d\n", total_files, total_blank, total_comment, total_code,
                 total_lines);
        strcat(output, output_line);
        strcat(output, "-------------------------------------------------------------------------------------------\n");
    }

    printf("%s", output);
    free(output);
    free(output_line);
    free(language_summary_groups);
}
