FROM archlinux:latest

# srcs
ADD https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.gz /root/src/
ADD https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.gz /root/src/

# pkgs
RUN pacman -Syy && \
    pacman -S base-devel gmp libmpc mpfr curl nasm --noconfirm

# environment
ENV PREFIX $HOME/opt/cross
ENV TARGET i686-elf
ENV PATH $PREFIX/bin:$PATH

RUN cd $HOME/src && \
    tar -xvf gcc-13.2.0.tar.gz --one-top-level && \
    tar -xvf binutils-2.42.tar.gz --one-top-level && \
    mkdir build-binutils && \
    cd build-binutils && \
    ../binutils-2.42/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror && \
    make && \
    make install && \

    cd $HOME/src && \
    mkdir build-gcc && \
    
    cd build-gcc && \
    ../gcc-13.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers && \
    make all-gcc && \
    make all-target-libgcc && \
    make install-gcc && \
    make install-target-libgcc