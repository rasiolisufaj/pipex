# pipex

Simplified version test:

    gcc simple_pipex.c -o pipex

    echo -e "hello world\nhi\nhello 42" > infile
    ./pipex infile "grep hello" "wc -l" outfile
    cat outfile