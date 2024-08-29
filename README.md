# TLOC - Total Lines of Code

*Note: This is a work in progress and has only been tested on ARM based MacOS.*

## Table of Contents
- [Quick Start](#quick-start)
- [Overview](#overview)
- [Install](#install)
    - [Install From Source](#install-from-source)
- [Usage](#usage)
    - [Usage Caveats](#usage-caveats)
    - [Options](#options)
- [Supported Languages](#supported-languages)
- [Contributing](#contributing)
- [License](#license)

## Quick Start

Step 1: Download tloc. Checkout how to [install](#install) tloc below.

Step 2: Open a terminal.

Step 3: Invoke tloc, passing in a file or directory, to count blank lines, comment 
lines, and source code lines, displaying results per file.

<details>
<summary>CWD</summary>
<pre>
$ tloc
------------------------------------------------------------------------------------------------
File name                                    blank        comment           code          total
------------------------------------------------------------------------------------------------
./utils.h                                        2              0              7              9
./language.h                                     4              0             13             17
./app.h                                          5              0             29             34
./utils.c                                       16             40             49            105
./language.c                                     9             15             50             74
./summary.h                                      2              0             11             13
./tloc.c                                         3              0             15             18
./app.c                                         45             20            309            374
------------------------------------------------------------------------------------------------
TOTAL:                                          86             75            483            644
------------------------------------------------------------------------------------------------
</pre>
</details>

<details>
<summary>File</summary>
<pre>
$ tloc src/tloc.c
------------------------------------------------------------------------------------------------
file name                                    blank        comment           code          total
------------------------------------------------------------------------------------------------
./tloc.c                                         3              0             15             18
</pre>
</details>

<details>
<summary>Directory</summary>
<pre>
$ tloc ./src
------------------------------------------------------------------------------------------------
file name                                    blank        comment           code          total
------------------------------------------------------------------------------------------------
./utils.h                                        2              0              7              9
./language.h                                     4              0             13             17
./app.h                                          5              0             29             34
./utils.c                                       16             40             49            105
./language.c                                     9             15             50             74
./summary.h                                      2              0             11             13
./tloc.c                                         3              0             15             18
./app.c                                         45             20            309            374
------------------------------------------------------------------------------------------------
total:                                          86             75            483            644
------------------------------------------------------------------------------------------------
</pre>
</details>

## Overview

Developed in C with no dependencies beyond the standard library, `tloc` offers a 
straightforward approach to counting lines of code. As of August 22, 2024, `tloc` 
parses each file line by line, performing the following checks:

1. **Blank Lines**: If a line is empty or an espace sequence representing whitespace,
it is counted as a blank line.
1. **Multiline Comment Start**: If a line *begins* with characters indicating the
start of a multiline comment block, tloc recognizes it as the beginning of a comment.
1. **Within Multiline Comment**: Lines within a multiline comment block are counted
as comments until the end of the block is detected.
1. **Single Line Comment**: If a line *begins* with characters that denote a single-line
comment, it is counted as a comment.
1. **Source Code**: Any line that does not meet the above conditions is counted
as source code.

For more detailed examples and explanations, refer to [calculations.md](./docs/calculations.md)

## Install

### Install From Source

1. Clone the repo

```sh 
git clone https://github.com/navazjm/tloc.git
```

2. cd into tloc

```sh 
cd tloc
```

#### MacOS & Linux

Either run the install script or manually build with CMake

##### Script

1. Run the install script 

```sh 
sudo ./scripts/install.sh
```

*Note: The install script runs the commands found in the following CMake section.
Use `sudo` to move `tloc` executable into `/usr/local/bin/`. This requires
elevated privilages and allows you to use `tloc` from any directory*

##### CMake  

1. Create `build` dir and cd into it

```sh 
mkdir build && cd build
```

2. Run cmake

```sh 
cmake ..
```

3. Run make

```sh 
sudo make install
```

*Note: Use `sudo` to move `tloc` executable into `/usr/local/bin/`. This requires
elevated privilages and allows you to use `tloc` from any directory*

## Usage

```sh
$ tloc optional/file/path [options]
```

By default, tloc will use your cwd as your file path. Also, tloc will only parse files 
returned from running `git ls-files <path>`, i.e., files tracked by Git. Lastly, by 
default, tloc will display lines of code per file and not by language.

### Usage Caveats

There are two small caveats when passing in a file or directory.

1. The path must be the second command-line argument, i.e, directory follow the tloc 
executable. Otherwise, tloc will fallback to CWD.

Incorrect:

```sh 
./tloc -iu /src
```

Correct:

```sh 
./tloc /src -iu
```

2. If you are in a directory within a Git-managed project, you must include the flag 
`-iu` or `--include-untracked` when pasing in a directory path outside the root of the 
Git-managed project.

Incorrect:

```sh 
./tloc /Users/michaelnavarro/repos/ultrashub/web/src/lib
fatal: /Users/michaelnavarro/repos/ultrashub/web/src/lib: '/Users/michaelnavarro/repos/ultrashub/web/src/lib' is outside repository at '/Users/michaelnavarro/repos/tloc'
```

Correct:

```sh 
./tloc /Users/michaelnavarro/repos/ultrashub/web/src/lib -iu
------------------------------------------------------------------------------------------------
File name                                    blank        comment           code          total
------------------------------------------------------------------------------------------------
./firebase.ts                                    5              1             29             35
./axios.ts                                       2              0             10             12
./shadcn.ts                                      1              0              5              6
------------------------------------------------------------------------------------------------
TOTAL:                                           8              1             44             53
------------------------------------------------------------------------------------------------
```

### Options

```sh 
$ tloc --help
USAGE:
    tloc optional/path/ [options]

OPTIONAL FILE PATH:

* Can be a path to a directory or a specific file
* Will default to CWD, if one of the following conditions is met:
    1. Omitted
    2. Path does not exist
    3. Do not have read access permisions
    4. Not provided as the second command-line arg.

META OPTIONS:
    -h, --help                           Display list of command-line options.
    -v, --version                        Display installed version of tloc.
    -sl, --supported-languages           Display a list of supported programming languages.

FILTERING AND SORTING OPTIONS:
    -iu, --include-untracked             Include files not being tracked by Git.

DISPLAYING OPTIONS:
    -l, --language                       List data by programming languages, not by files.
    -eu, --exclude-unsupported           Exclude unsupported file types/langauges from being displayed.
    -pp, --print-parent                  Print file name as parent/filename.
    -pp-s, --print-parent-short          Print file name as p/filename.
    -pp-a, --print-parent-all            Print file name including all parent dirs relative to provided path.
    -pp-as, --print-parent-all-short     Print file name including only first letter for all parent dirs relative to provided path.

For more details, please visit: https://github.com/navazjm/tloc/blob/main/docs/options.md
```

For detailed options' documentation, checkout [options.md](./docs/options.md)

## Supported Languages

```sh 
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
```

Interested in adding a new language? Start a [discussion](https://github.com/navazjm/tloc/discussions),
and we can work together to incorporate it into tloc!

## Contributing 

Want to contribute to tloc? Awesome, we would love your input ♥\
\
If you have a feature request, start a [discussion](https://github.com/navazjm/tloc/discussions),
and we can work together to incorporate it into tloc!\
\
Encountered a defect? Please report it under [issues](https://github.com/navazjm/tloc/issues).
Be sure to include detailed information to help us address the issue effectively.\
\
Want to implement a feature request or fix a defect? Checkout our [contributing guide](./docs/contributing.md).

## License

TLOC is licensed under [GPL-3.0](./COPYING)
