pkgver=0.0.1
pkgname=cmdutil
pkgrel=1
pkgdesc="A novelty command-line utility"
arch=('x86_64')
url="https://github.com/itsnotqwerty/cmdutil-cpp"
license=('WTFPL')
depends=('gcc' 'make' 'boost')
source=("https://github.com/itsnotqwerty/cmdutil-cpp/archive/refs/tags/v$pkgver.tar.gz")

package() {
    make install DESTDIR="$pkgdir"
}

build() {
    make DESTDIR="$pkgdir"
}
