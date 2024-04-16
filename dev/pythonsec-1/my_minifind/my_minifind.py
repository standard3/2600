#!/usr/bin/env python3

import os
import stat
import argparse
import subprocess
import fnmatch
import pathlib

def parse_arguments() -> argparse.Namespace:
    """
    Parse CLI-provided arguments

    return: parsed args namespace
    """
    parser = argparse.ArgumentParser(description='Mini GNU find')

    # flags
    parser.add_argument(
        '-print',
        action=argparse.BooleanOptionalAction,
        help="""
            The -print action is performed on all files for which the whole expression is true, unless it contains an action other than -prune or -quit.  Actions which  inhibit  the  default
            -print are -delete, -exec, -execdir, -ok, -okdir, -fls, -fprint, -fprintf, -ls, -print and -printf.
        """)

    parser.add_argument(
        '-depth',
        action=argparse.BooleanOptionalAction,
        help="""
            Process each directory's contents before the directory itself.
        """)

    # parameters
    parser.add_argument(
        '-maxdepth',
        action="store",
        type=int,
        help="""
            Descend at most levels (a non-negative integer) levels of directories below the starting-points.  Using -maxdepth 0 means only apply the tests and actions to the starting-points themselves.
        """)

    parser.add_argument(
        '-mindepth',
        action="store",
        type=int,
        help="""
            Do not apply any tests or actions at levels less than levels (a non-negative integer).  Using -mindepth 1 means process all files except the starting-points.
        """)

    parser.add_argument(
        '-name',
        action="store",
        type=str,
        help="""
            Base of file name (the path with the leading directories removed) matches shell pattern pattern.  Because the leading directories are removed, the  file  names  considered
            for a match with -name will never include a slash, so ‘-name a/b' will never match anything (you probably need to use -path instead).  A warning is issued if you try to do
            this, unless the environment variable POSIXLY_CORRECT is set.  The metacharacters (‘*', ‘?', and ‘[]') match a ‘.' at the start of the base name (this is a change in find‐
            utils-4.2.2;  see section STANDARDS CONFORMANCE below).  To ignore a directory and the files under it, use -prune rather than checking every file in the tree; see an exam‐
            ple in the description of that action.  Braces are not recognised as being special, despite the fact that some shells including Bash imbue braces with a special meaning in
            shell patterns.  The filename matching is performed with the use of the fnmatch(3) library function.  Don't forget to enclose the pattern in quotes in order to protect  it
            from expansion by the shell.
        """)

    parser.add_argument(
        '-path',
        action="store",
        type=pathlib.Path,
        help="""
            File name matches shell pattern pattern.  The metacharacters do not treat ‘/' or ‘.' specially; so, for example,
                  find . -path "./sr*sc"
            will  print  an  entry  for a directory called ./src/misc (if one exists).  To ignore a whole directory tree, use -prune rather than checking every file in the tree.  Note
            that the pattern match test applies to the whole file name, starting from one of the start points named on the command line.  It would only make sense to use  an  absolute
            path name here if the relevant start point is also an absolute path.  This means that this command will never match anything:
                find bar -path /foo/bar/myfile -print
            Find  compares  the  -path argument with the concatenation of a directory name and the base name of the file it's examining.  Since the concatenation will never end with a
            slash, -path arguments ending in a slash will match nothing (except perhaps a start point specified on the command line).  The predicate -path is also supported  by  HP-UX
            find and is part of the POSIX 2008 standard.
        """)

    parser.add_argument(
        '-type',
        action="store",
        choices=['b', 'c', 'd', 'p', 'f', 'l', 's', 'D'],
        help="""
            File is of type c:

              b      block (buffered) special

              c      character (unbuffered) special

              d      directory

              p      named pipe (FIFO)

              f      regular file

              l      symbolic link; this is never true if the -L option or the -follow option is in effect, unless the symbolic link is broken.  If you want to search for symbolic links
                     when -L is in effect, use -xtype.

              s      socket

              D      door (Solaris)

              To search for more than one type at once, you can supply the combined list of type letters separated by a comma ‘,' (GNU extension).
        """)

    parser.add_argument(
        '-exec',
        action="store",
        type=str,
        help="""
            Execute  command;  true  if  0 status is returned.  All following arguments to find are taken to be arguments to the command until an argument consisting of ‘;' is encoun‐
            tered.  The string ‘{}' is replaced by the current file name being processed everywhere it occurs in the arguments to the command, not just in arguments where it is alone,
            as in some versions of find.  Both of these constructions might need to be escaped (with a ‘\') or quoted to protect them from expansion by the shell.   See  the  EXAMPLES
            section  for  examples of the use of the -exec option.  The specified command is run once for each matched file.  The command is executed in the starting directory.  There
            are unavoidable security problems surrounding use of the -exec action; you should use the -execdir option instead.
        """)

    args = parser.parse_args()

    return args

def is_matching_file_type(path: pathlib.Path, file_type: chr) -> bool:
    """
    Check if provided @path file type matches @file_type

    ...
    """
    file_mode = path.stat().st_mode

    match file_type:
        case '*':
            return True
        case 'b':
            return stat.S_ISBLK(file_mode)
        case 'c':
            return stat.S_ISCHR(file_mode)
        case 'd':
            return stat.S_ISDIR(file_mode)
        case 'p':
            return stat.S_ISFIFO(file_mode)
        case 'f':
            return stat.S_ISREG(file_mode)
        case 'l':
            return stat.S_ISLNK(file_mode)
        case 's':
            return stat.S_ISSOCK(file_mode)
        case 'D':
            return stat.S_ISDOOR(file_mode)
        case _:
            return False

def get_files_in_path(
    path: pathlib.Path,
    name: str,
    file_type: chr,
    maxdepth: int,
    mindepth: int,
    topdown: bool
    ) -> list:
    """
    Get all files in provided @path globbing from @name
    matching @type between @mindepth and @maxdepth

    @path: path to search in
    @name: name or glob
    @type: type of file
    @maxdepth: maximum depth to recurse in
    @mindepth: do not apply any tests or actions at levels less than this

    @return: filtered and matching files in @path
    """
    files = []

    for (root, dirs, files) in os.walk(path, topdown=topdown):

        depth = root.count(os.sep) - str(path).count(os.sep)

        if depth > maxdepth or depth < mindepth: continue

        for name in files + dirs:
            fullpath = pathlib.Path(root + name)

            # name check
            if name and not fnmatch.fnmatch(fullpath, name):
                continue

            # type check
            if file_type and not is_matching_file_type(fullpath, file_type):
                continue

            files.append(fullpath)

    return files

def main() -> None:
    parsed_args = parse_arguments()

    # todo: sanitize & validate user input

    path = pathlib.Path(parsed_args.path) if parsed_args.path else pathlib.Path.cwd()
    name = parsed_args.name if parsed_args.name else "*"

    file_type = parsed_args.type if parsed_args.type else "*"

    depth = False if parsed_args.depth else True
    maxdepth = parsed_args.maxdepth if parsed_args.maxdepth else 1
    mindepth = parsed_args.mindepth if parsed_args.mindepth else 1

    files = get_files_in_path(path, name, file_type, maxdepth, mindepth, depth)

    # exec sur chaque path si besoin (avec subprocess)
    for file in files:
        print(file)


if __name__ == "__main__":
    main()