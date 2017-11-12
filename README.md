# t3
A game of advanced Tic-Tac-Toe.

## Installation
First either clone the github repository to your local filesystem with `git clone https://www.github.com/klmanion/t3.git`,
or obtain a versioned tarball release and extract it.

Navigate to the project's main directory ('t3') and run the following commands
```bash
./autogen.sh
./configure
make
make install
```

If you have a tarball, running `./autogen.sh` might be unnecessary.

## Development Builds
The latter describes how to get a stable running build.  If you would like a possibly unstable development build then simply obtain the repository with `git clone --branch 'dev' https://www.github.com/klmanion/t3.git`, then compile identically as above.
