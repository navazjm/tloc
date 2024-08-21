# TLOC - Total Lines of Code

## Table of Contents
- [Quick Start](#quick-start)
- [Overview](#overview)
- [License](#license)
- [Install](#install)
- [Usage](#usage)
    - [Usage Caveats](#usage-caveats)
    - [Options](#options)
- [Supported Languages](#supported-languages)
- [Contributing](#contributing)

## Quick Start

## Overview

## License

## Install

## Usage

```sh
$ tloc optional/file/path [options]
```

By default, tloc will use your cwd as your file path. Also, tloc will only parse files 
returned from running `git ls-files <path>`, i.e., files tracked by Git. Lastly, by 
default, tloc will display lines of code per file and not by language. So if you 
are in the src folder of tloc, you will get a result similar to:

```sh 
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
```

You may provide a path to a directory of files you want tloc to parse. If you are 
in the root of the tloc project, but only want to parse the `src` directory, you can 
run the following command:

```sh 
$ tloc src
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
```

You may also provide a path to a single file you want tloc to parse. If you are 
in the root of the tloc project, but only want to parse `./src/tloc.c`, you can 
run the following command:

```sh 
$ tloc src/tloc.c
------------------------------------------------------------------------------------------------
file name                                    blank        comment           code          total
------------------------------------------------------------------------------------------------
./tloc.c                                         3              0             15             18
```

### Usage Caveats

There are two small caveats when passing in a file or directory.

1. The path must be the second command-line argument, i.e, directoy follow the tloc 
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
USAGE: tloc optional/file/path [options]

OPTIONAL FILE PATH:

* Can be a path to a directory or a specific file
* Will default to CWD, if one of the following conditions is met:
    1. Omitted
    2. Path does not exist
    3. Do not have read access permisions
    4. Not provided as the second command-line arg.

META OPTIONS:
    -h, --help                      Display list of command-line options.
    -v, --version                   Display version of tloc.
    -sl, --supported-languages      Display a list of supported programming languages.

FILTERING AND SORTING OPTIONS:
    -iu, --include-untracked        Include files not being tracked by Git.

DISPLAY OPTIONS:
    -l, --language                  List data by programming languages, not by files.
    -fp, --full-path                Expand file name to show full path
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

