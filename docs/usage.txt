USAGE:
  tloc optional/path [options]

OPTIONAL PATH:

* Can be a path to a directory or a specific file
* Will default to CWD, if one of the following conditions are met:
    1. Omitted
    2. Path does not exist
    3. Do not have read access permisions
    4. Not provided as the second command-line arg.
        Ex: "$ tloc /path/to/files"    -> will set path to /path/to/files
        Ex: "$ tloc -l /path/to/files" -> will ignore /path/to/files

META OPTIONS:
    -h, --help                      Display list of command-line options.
    -v, --version                   Display version of tloc.
    -sl, --supported-languages      Display a list of supported programming languages.

FILTERING AND SORTING OPTIONS:
    -iu, --include-untracked        Include files not being tracked by Git.

DISPLAY OPTIONS:
    -l, --language                  List data by programming languages, not by files.

-------------------------------------------------------------------------------

To add a new option:
1. Update this file with the new shorthand, longhand, and description of the option
2. In src/app.c, modify loc_app_parse_cmd_args to include the new option
3. Also, in src/app.c, modify tloc_print_usage_help to include the new option
