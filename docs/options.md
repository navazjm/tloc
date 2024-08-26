# Options (Command Line Argumnets)

## Overview

By default, when `tloc` is ran without any command-line arguments, it uses the 
current working directory (`cwd`) as the file path to parse. It will only parse 
files returned by `git ls-files <path>`, and it renders data for each file individually. 
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
Files with an unsupported language will be tracked as `N/A` where only total lines
is counted.
</details>

---

## FILTERING AND SORTING OPTIONS:

### Include Untracked Option

**Shorthand**:   `-iu`\
**Longhand**:    `--include-untracked`\
**Description**: Include files not being tracked by Git. 

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
running `tloc` without `-iu` flag, will ignore the untracked file. 

<pre> 
$ tloc src
------------------------------------------------------------------------------------------------
File name                                    blank        comment           code          total
------------------------------------------------------------------------------------------------
./app.c                                         55             21            367            443
./app.h                                          6              0             30             36
./language.c                                    10             18             50             78
./language.h                                     4              0             13             17
./summary.c                                      2              3             19             24
./summary.h                                      4              0             21             25
./tloc.c                                         3              0             15             18
./utils.c                                       16             40             49            105
./utils.h                                        2              0              7              9
------------------------------------------------------------------------------------------------
TOTAL:                                         102             82            571            755
------------------------------------------------------------------------------------------------
</pre>
<pre>
$ tloc src -iu
------------------------------------------------------------------------------------------------
File name                                    blank        comment           code          total
------------------------------------------------------------------------------------------------
./utils.h                                        2              0              7              9
./language.h                                     4              0             13             17
./app.h                                          6              0             30             36
./summary.c                                      2              3             19             24
./utils.c                                       16             40             49            105
./file_not_tracked.c                             0              0              0              0
./language.c                                    10             18             50             78
./summary.h                                      4              0             21             25
./tloc.c                                         3              0             15             18
./app.c                                         55             21            367            443
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

#### Full Path Option

**Shorthand**:   `-fp`\
**Longhand**:    `--full-path`\
**Description**: Expand file name to show full path. 

<details>
<summary>View Usage</summary>
<pre>
$ tloc ../aoc/2023/src -iu -fp
------------------------------------------------------------------------------------------------
File name                                    blank        comment           code          total
------------------------------------------------------------------------------------------------
../aoc/2023/src/day_05/day_05.cpp               10              4             55             69
../aoc/2023/src/day_05/day_05.h                  3              0              8             11
../aoc/2023/src/day_02/day_02.cpp                3              0             87             90
../aoc/2023/src/day_02/day_02.h                  3              0              8             11
../aoc/2023/src/day_03/day_03.h                  3              0              8             11
../aoc/2023/src/day_03/day_03.cpp                5              0            110            115
../aoc/2023/src/day_04/day_04.cpp                3              0             70             73
../aoc/2023/src/day_04/day_04.h                  3              0              8             11
../aoc/2023/src/template/day_x.h                 3              0              8             11
../aoc/2023/src/template/day_x.cpp               2              0              8             10
../aoc/2023/src/day_01/day_01.cpp                5              0             68             73
../aoc/2023/src/day_01/day_01.h                  3              0              8             11
../aoc/2023/src/day_06/day_06.cpp                7              0             67             74
../aoc/2023/src/day_06/day_06.h                  3              0              8             11
../aoc/2023/src/day_08/day_08.h                  3              0              8             11
../aoc/2023/src/day_08/day_08.cpp               15              0             98            113
../aoc/2023/src/day_09/day_09.h                  3              0              8             11
../aoc/2023/src/day_09/day_09.cpp                8              0             79             87
../aoc/2023/src/day_07/day_07.h                  3              0              8             11
../aoc/2023/src/day_07/day_07.cpp               19              3            133            155
../aoc/2023/src/main.cpp                         6              0            104            110
------------------------------------------------------------------------------------------------
TOTAL:                                         113              7            959           1079
------------------------------------------------------------------------------------------------
</pre>
<pre>
$ tloc ../aoc/2023/src -iu
------------------------------------------------------------------------------------------------
File name                                    blank        comment           code          total
------------------------------------------------------------------------------------------------
./day_05/day_05.cpp                             10              4             55             69
./day_05/day_05.h                                3              0              8             11
./day_02/day_02.cpp                              3              0             87             90
./day_02/day_02.h                                3              0              8             11
./day_03/day_03.h                                3              0              8             11
./day_03/day_03.cpp                              5              0            110            115
./day_04/day_04.cpp                              3              0             70             73
./day_04/day_04.h                                3              0              8             11
./template/day_x.h                               3              0              8             11
./template/day_x.cpp                             2              0              8             10
./day_01/day_01.cpp                              5              0             68             73
./day_01/day_01.h                                3              0              8             11
./day_06/day_06.cpp                              7              0             67             74
./day_06/day_06.h                                3              0              8             11
./day_08/day_08.h                                3              0              8             11
./day_08/day_08.cpp                             15              0             98            113
./day_09/day_09.h                                3              0              8             11
./day_09/day_09.cpp                              8              0             79             87
./day_07/day_07.h                                3              0              8             11
./day_07/day_07.cpp                             19              3            133            155
./main.cpp                                       6              0            104            110
------------------------------------------------------------------------------------------------
TOTAL:                                         113              7            959           1079
------------------------------------------------------------------------------------------------
</pre>

By default, if `-fp` is not passed in and the provided path is a directory of files,
`tloc` will trim the provided path from each individual file name to save on space
when displaying.

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
1. Update documentation:
    - Update this file with the new shorthand, longhand, description, and example usage of the option
    - In README, update usage section displaying result of `tloc -h`  
