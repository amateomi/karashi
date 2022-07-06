<div align="center">
  <h1> 殻 </h1>
  Kara is basic Linux shell, indeed

  ![image](https://user-images.githubusercontent.com/107575122/174137564-0a3d5380-5e23-4aa7-a26f-6466ac3aaa30.png)
</div>

## About The Project

The main purpose of this project is a curiosity in system programming. I was using such shell giants as zsh and fish
with abnormal amount of features. So I decided to deep dive on this topic. As the result Kara was born, minimalistic
usable Linux shell.

### Implemented Features

- execution of different programs
- two builtin commands: <code>cd</code>, <code>exit</code>
- redirecting keyboard signals such as <code>^C</code> to current execution processes instead of shell
- I/O redirecting via <code><</code>, <code>></code> and <code>2></code> for programs
- piping via <code>|</code> symbol
- expansion <code>~</code> to home directory path
- reading environment variables with <code>$</code> symbol (<code>echo $USER</code> will print current user instead of
  $USER)
- commands history and input processing with emacs bindings are implemented with GNU readline library

## Getting Started

Kara is Linux shell, and I didn't try to run in on macOS or FreeBSD, but you free to do it and leave messages in the
issues section.

### Dependencies

Kara depends on the GNU readline library. I suspect that any version is fine. Also, you'll need git, gcc and make,
which are preinstalled on most Linux distributions.

**Ubuntu:**

``` shell
sudo apt install libreadline-dev
```

**Fedora:**

``` shell
sudo dnf install readline readline-devel
```

**Arch:**

``` shell
sudo pacman -S readline
```

### Installing

``` shell
git clone https://github.com/amaom1/karashi.git
cd karashi
make && sudo make install
```

### Uninstalling

In karashi directory enter that command:

``` shell
sudo make uninstall
```

Now Kara is not installed in your $PATH and you free to delete repository too.
  
### Tests

Kara provides some kind of overview of what it is capable of. To run it just enter that command after building project:

``` shell
make test
```
  
### Documentation
  
Kara provides auto-generated documentation via Doxygen. If you are interested in the project structure but don't want
to view the source code, you can check out the documentation on the [GitHub pages](https://amateomi.github.io/karashi/html/index.html).
