# Options (Command Line Argumnets)

## Overview

By default, when `tloc` is ran without any command-line arguments, `tloc` will use 
your current working directory (`cwd`), rendering data for each file individually. 
Using the options listed below, you can customize how `tloc` renders the data to 
suit your preferences.

## META OPTIONS:

### Help Option

**Shorthand**:   `-h`\
**Longhand**:    `--help`\
**Description**: Display list of command-line options.

---

### Version Option

**Shorthand**:   `-v`\
**Longhand**:    `--version`\
**Description**: Display installed version of tloc. 

---

### Supported Language Option

**Shorthand**:   `-sl`\
**Longhand**:    `--supported-languages`\
**Description**: Display a list of supported programming languages.

<details>
<summary>View Usage</summary>
<pre>
$ tloc -sl
----------------------------------
Language             Extensions
----------------------------------
C                    c
C/C++ Header         h, hpp
C++                  cpp
Markdown             md
JavaScript           js
TypeScript           ts
</pre>
</details>

---

## FILTERING AND SORTING OPTIONS:

### Git Option

**Shorthand**:   `-g`\
**Longhand**:    `--git`\
**Description**: Only include files being tracked by Git. 

<details>
<summary>View Usage</summary>
<pre>
$ git status
On branch main
Your branch is up to date with 'origin/main'.

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        src/file_not_tracked.c

no changes added to commit (use "git add" and/or "git commit -a")
</pre>

Using git status, you can see `src/file_not_tracked.c` is an untracked file. Therefore,
running `tloc` with `-g` flag, will ignore the untracked file. 

<pre> 
$ tloc src
------------------------------------------------------------------------------------------------
File name                                    blank        comment           code          total
------------------------------------------------------------------------------------------------
utils.h                                        2              0              7              9
language.h                                     4              0             13             17
app.h                                          6              0             30             36
summary.c                                      2              3             19             24
utils.c                                       16             40             49            105
file_not_tracked.c                             0              0              0              0
language.c                                    10             18             50             78
summary.h                                      4              0             21             25
tloc.c                                         3              0             15             18
app.c                                         55             21            367            443
------------------------------------------------------------------------------------------------
TOTAL:                                         102             82            571            755
------------------------------------------------------------------------------------------------
</pre>
<pre>
$ tloc src -g
------------------------------------------------------------------------------------------------
File name                                    blank        comment           code          total
------------------------------------------------------------------------------------------------
app.c                                         55             21            367            443
app.h                                          6              0             30             36
language.c                                    10             18             50             78
language.h                                     4              0             13             17
summary.c                                      2              3             19             24
summary.h                                      4              0             21             25
tloc.c                                         3              0             15             18
utils.c                                       16             40             49            105
utils.h                                        2              0              7              9
------------------------------------------------------------------------------------------------
TOTAL:                                         102             82            571            755
------------------------------------------------------------------------------------------------
</pre>
</details>

---

## DISPLAY OPTIONS:

### Language Option

**Shorthand**:   `-l`\
**Longhand**:    `--language`\
**Description**: List data by programming languages, not by files. 

<details>
<summary>View Usage</summary>
<pre>
$ tloc -l
-------------------------------------------------------------------------------------------
Language                 files          blank        comment           code          total
-------------------------------------------------------------------------------------------
N/A                          8              0              0              0            749
Markdown                     5            104              0            310            414
C                            5             86             82            500            668
C/C++ Header                 4             16              0             71             87
-------------------------------------------------------------------------------------------
TOTAL:                      22            206             82            881           1918
-------------------------------------------------------------------------------------------
</pre>
Files with an unsupported language will be tracked as `N/A` where only total lines
is counted.
</details>

---

### Exclude Unsupported Option

**Shorthand**:   `-eu`\
**Longhand**:    `--exclude-unsupported`\
**Description**: Exclude unsupported file types/langauges from being displayed. 

<details>
<summary>View Usage</summary>
<pre>
$ tloc -l -eu
-------------------------------------------------------------------------------------------
Language                 files          blank        comment           code          total
-------------------------------------------------------------------------------------------
Markdown                     5            111              0            324            435
C                            5             86             82            500            668
C/C++ Header                 4             16              0             71             87
-------------------------------------------------------------------------------------------
TOTAL:                      14            213             82            895           1190
-------------------------------------------------------------------------------------------
</pre>
<pre>
$ tloc -l
-------------------------------------------------------------------------------------------
Language                 files          blank        comment           code          total
-------------------------------------------------------------------------------------------
N/A                          8              0              0              0            749
Markdown                     5            104              0            310            414
C                            5             86             82            500            668
C/C++ Header                 4             16              0             71             87
-------------------------------------------------------------------------------------------
TOTAL:                      22            206             82            881           1918
-------------------------------------------------------------------------------------------
</pre>

Comparing `tloc -l -eu` and `tloc -l`, you can see that the `N/A` grouping is no 
longer being rendered. If you omit `-l` option, files whose supported language 
is not known, will also not be displayed.

</details>

---

### Print Parent Option

**Shorthand**:   `-pp`\
**Longhand**:    `--print-parent`\
**Description**: Print file name as parent/filename. 

<details>
<summary>View Usage</summary>
<pre>
$ tloc -g -pp
------------------------------------------------------------------------------------------------
File name                                    blank        comment           code          total
------------------------------------------------------------------------------------------------
/.clang-format                                   0              0              0              5
/.gitignore                                      0              0              0             60
/.gitmodules                                     0              0              0              3
/CMakeLists.txt                                  0              0              0             36
/COPYING                                         0              0              0            621
/README.md                                      64              0            213            277
/docs/calculations.md                           36              0            102            138
/docs/code-of-conduct.md                        18              0             56             74
/docs/contributing.md                            9              0             18             27
/docs/options.md                                51              0            207            258
/scripts/debug.sh                                0              0              0             16
/scripts/install.sh                              0              0              0              5
/scripts/run.sh                                  0              0              0             16
/scripts/test.sh                                 0              0              0             16
/src/app.c                                      52             20            340            412
/src/app.h                                       4              0             23             27
/src/language.c                                 10             20             51             81
/src/language.h                                  4              0             13             17
/src/options.c                                  13             16            113            142
/src/options.h                                  10              0             52             62
/src/summary.c                                   6              3             47             56
/src/summary.h                                   7              0             31             38
/src/tloc.c                                      2              0             11             13
/src/utils.c                                    22             59            121            202
/src/utils.h                                     3              0             10             13
/tests/language_test.c                           4              0             29             33
/tests/language_test.h                           3              0              7             10
/tests/options_test.c                            6              2             53             61
/tests/options_test.h                            3              0              7             10
/tests/tloc_test.c                               2              0             12             14
/tests/utils_test.c                             25              0            146            171
/tests/utils_test.h                              3              0             12             15
/vendors/munit                                   0              0              0              0
------------------------------------------------------------------------------------------------
TOTAL:                                         357            120           1674           2929
------------------------------------------------------------------------------------------------
</pre>
</details>

---

### Parent Parent Short Option

**Shorthand**:   `-pp-s`\
**Longhand**:    `--print-parent-short`\
**Description**: Print file name as p/filename. 

<details>
<summary>View Usage</summary>
<pre>
$ tloc -g -pp-s
------------------------------------------------------------------------------------------------
File name                                    blank        comment           code          total
------------------------------------------------------------------------------------------------
/.clang-format                                   0              0              0              5
/.gitignore                                      0              0              0             60
/.gitmodules                                     0              0              0              3
/CMakeLists.txt                                  0              0              0             36
/COPYING                                         0              0              0            621
/README.md                                      64              0            213            277
/d/calculations.md                              36              0            102            138
/d/code-of-conduct.md                           18              0             56             74
/d/contributing.md                               9              0             18             27
/d/options.md                                   51              0            247            298
/s/debug.sh                                      0              0              0             16
/s/install.sh                                    0              0              0              5
/s/run.sh                                        0              0              0             16
/s/test.sh                                       0              0              0             16
/s/app.c                                        52             20            340            412
/s/app.h                                         4              0             23             27
/s/language.c                                   10             20             51             81
/s/language.h                                    4              0             13             17
/s/options.c                                    13             16            113            142
/s/options.h                                    10              0             52             62
/s/summary.c                                     6              3             47             56
/s/summary.h                                     7              0             31             38
/s/tloc.c                                        2              0             11             13
/s/utils.c                                      22             59            121            202
/s/utils.h                                       3              0             10             13
/t/language_test.c                               4              0             29             33
/t/language_test.h                               3              0              7             10
/t/options_test.c                                6              2             53             61
/t/options_test.h                                3              0              7             10
/t/tloc_test.c                                   2              0             12             14
/t/utils_test.c                                 25              0            146            171
/t/utils_test.h                                  3              0             12             15
/v/munit                                         0              0              0              0
------------------------------------------------------------------------------------------------
TOTAL:                                         357            120           1714           2969
------------------------------------------------------------------------------------------------
</pre>
</details>

---

### Parent Parent All Option

**Shorthand**:   `-pp-a`\
**Longhand**:    `--print-parent-all`\
**Description**: Print file name including all parent dirs relative to provided path.

<details>
<summary>View Usage</summary>
<pre>
$ tloc -g -pp-a
------------------------------------------------------------------------------------------------
File name                                    blank        comment           code          total
------------------------------------------------------------------------------------------------
/.clang-format                                   0              0              0              5
/.gitignore                                      0              0              0             60
/.gitmodules                                     0              0              0              3
/CMakeLists.txt                                  0              0              0             36
/COPYING                                         0              0              0            621
/README.md                                      64              0            213            277
/docs/calculations.md                           36              0            102            138
/docs/code-of-conduct.md                        18              0             56             74
/docs/contributing.md                            9              0             18             27
/docs/options.md                                51              0            247            298
/scripts/debug.sh                                0              0              0             16
/scripts/install.sh                              0              0              0              5
/scripts/run.sh                                  0              0              0             16
/scripts/test.sh                                 0              0              0             16
/src/app.c                                      52             20            340            412
/src/app.h                                       4              0             23             27
/src/language.c                                 10             20             51             81
/src/language.h                                  4              0             13             17
/src/options.c                                  13             16            113            142
/src/options.h                                  10              0             52             62
/src/summary.c                                   6              3             47             56
/src/summary.h                                   7              0             31             38
/src/tloc.c                                      2              0             11             13
/src/utils.c                                    22             59            121            202
/src/utils.h                                     3              0             10             13
/tests/language_test.c                           4              0             29             33
/tests/language_test.h                           3              0              7             10
/tests/options_test.c                            6              2             53             61
/tests/options_test.h                            3              0              7             10
/tests/tloc_test.c                               2              0             12             14
/tests/utils_test.c                             25              0            146            171
/tests/utils_test.h                              3              0             12             15
/vendors/munit                                   0              0              0              0
------------------------------------------------------------------------------------------------
TOTAL:                                         357            120           1714           2969
------------------------------------------------------------------------------------------------
</pre>
</details>

---

### Parent Parent All Option

**Shorthand**:   `-pp-as`\
**Longhand**:    `--print-parent-all-short`\
**Description**:Print file name including only first letter for all parent dirs relative to provided path. 

<details>
<summary>View Usage</summary>
<pre>
$ tloc -g -pp-as
------------------------------------------------------------------------------------------------
File name                                    blank        comment           code          total
------------------------------------------------------------------------------------------------
/.clang-format                                   0              0              0              5
/.gitignore                                      0              0              0             60
/.gitmodules                                     0              0              0              3
/CMakeLists.txt                                  0              0              0             36
/COPYING                                         0              0              0            621
/README.md                                      64              0            213            277
/d/calculations.md                              36              0            102            138
/d/code-of-conduct.md                           18              0             56             74
/d/contributing.md                               9              0             18             27
/d/options.md                                   51              0            247            298
/s/debug.sh                                      0              0              0             16
/s/install.sh                                    0              0              0              5
/s/run.sh                                        0              0              0             16
/s/test.sh                                       0              0              0             16
/s/app.c                                        52             20            340            412
/s/app.h                                         4              0             23             27
/s/language.c                                   10             20             51             81
/s/language.h                                    4              0             13             17
/s/options.c                                    13             16            113            142
/s/options.h                                    10              0             52             62
/s/summary.c                                     6              3             47             56
/s/summary.h                                     7              0             31             38
/s/tloc.c                                        2              0             11             13
/s/utils.c                                      22             59            121            202
/s/utils.h                                       3              0             10             13
/t/language_test.c                               4              0             29             33
/t/language_test.h                               3              0              7             10
/t/options_test.c                                6              2             53             61
/t/options_test.h                                3              0              7             10
/t/tloc_test.c                                   2              0             12             14
/t/utils_test.c                                 25              0            146            171
/t/utils_test.h                                  3              0             12             15
/v/munit                                         0              0              0              0
------------------------------------------------------------------------------------------------
TOTAL:                                         357            120           1714           2969
------------------------------------------------------------------------------------------------
</pre>
</details>

---

## Adding a new option

1. Add option to global list of valid args `const TLOC_Arg tloc_args[]` in `src/options.c`
    - If option is a meta option (these options run a separate process that normally terminates program after running): 
        1. modify `tloc_app_parse_cmd_args()` in `src/app.c` to include the new option
        1. define inline `TLOC_Set_Option_Func` function as `NULL`
    - If option is NOT a meta option:
        1. define inline `TLOC_Set_Option_Func` function
1. Update both `const size_t tloc_args_filtering_sorting_starting_idx` and `const size_t tloc_args_displaying_starting_idx` in `src/options.c`
1. Implement the logic to parse/render data based on the new option.
1. Add tests
1. Update documentation:
    - Update this file with the new shorthand, longhand, description, and example usage of the option
    - In README, update usage section displaying result of `tloc -h`  
