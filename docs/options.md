# Options (Command Line Argumnets)

## Overview

By default, when `tloc` is ran without any command-line arguments, it uses the 
current working directory (`cwd`) as the file path to parse. It will only parse 
files returned by `git ls-files <path>`, and it renders data for each file individually. 
Using the options listed below, you can customize how `tloc` renders the data to 
suit your preferences.

### META OPTIONS:

- `-h`, `--help` -> Display list of command-line options.

- `-v`, `--version` -> Display installed version of tloc.

- `-sl`, `--supported-languages` -> Display a list of supported programming languages.

<details>
<summary>More info.</summary>
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
<br>
Files with an unsupported language will be tracked as `N/A` where only total lines
is counted.
<br>
</details>

### FILTERING AND SORTING OPTIONS:

- `-iu`, `--include-untracked` -> Include files not being tracked by Git.

### DISPLAY OPTIONS:

- `-l`, `--language` -> List data by programming languages, not by files.

- `-eu`, `--exclude-unsupported` -> Exclude unsupported file types/langauges from being displayed.

- `-fp`, `--full-path` -> Expand file name to show full path.

## Adding a new option

1. Update this file with the new shorthand, longhand, and description of the option
2. In src/app.c, modify `loc_app_parse_cmd_args` to include the new option
3. Also, in src/app.c, modify `tloc_print_usage_help` to include the new option
4. Finally, implement the logic to parse/render data based on the new option.
