Release Process
====================

<<<<<<< HEAD
* Update translations, see [translation_process.md](https://github.com/polispay/polis/blob/master/doc/translation_process.md#syncing-with-transifex)
* Update hardcoded [seeds](/contrib/seeds)
=======
* Update translations, see [translation_process.md](https://github.com/dashpay/dash/blob/master/doc/translation_process.md#synchronising-translations).
>>>>>>> pr/6

* Update manpages, see [gen-manpages.sh](https://github.com/dashpay/dash/blob/master/contrib/devtools/README.md#gen-manpagessh).

Before every minor and major release:

* Update [bips.md](bips.md) to account for changes since the last release.
* Update version in sources (see below)
* Write release notes (see below)
* Update `src/chainparams.cpp` nMinimumChainWork with information from the getblockchaininfo rpc.
* Update `src/chainparams.cpp` defaultAssumeValid  with information from the getblockhash rpc.
  - The selected value must not be orphaned so it may be useful to set the value two blocks back from the tip.
  - Testnet should be set some tens of thousands back from the tip due to reorgs there.
  - This update should be reviewed with a reindex-chainstate with assumevalid=0 to catch any defect
     that causes rejection of blocks in the past history.

Before every major release:

* Update hardcoded [seeds](/contrib/seeds/README.md). TODO: Give example PR for Dash
* Update [`BLOCK_CHAIN_SIZE`](/src/qt/intro.cpp) to the current size plus some overhead.

### First time / New builders

If you're using the automated script (found in [contrib/gitian-build.sh](/contrib/gitian-build.sh)), then at this point you should run it with the "--setup" command. Otherwise ignore this.

Check out the source code in the following directory hierarchy.

	cd /path/to/your/toplevel/build
	git clone https://github.com/polispay/gitian.sigs.git
	git clone https://github.com/polispay/polis-detached-sigs.git
	git clone https://github.com/devrandom/gitian-builder.git
	git clone https://github.com/polispay/polis.git

### polis Core maintainers/release engineers, update (commit) version in sources

<<<<<<< HEAD
	pushd ./polis
	contrib/verifysfbinaries/verify.sh
	configure.ac
	doc/README*
	doc/Doxyfile
	contrib/gitian-descriptors/*.yml
	src/clientversion.h (change CLIENT_VERSION_IS_RELEASE to true)
=======
- `configure.ac`:
    - `_CLIENT_VERSION_MAJOR`
    - `_CLIENT_VERSION_MINOR`
    - `_CLIENT_VERSION_REVISION`
    - Don't forget to set `_CLIENT_VERSION_IS_RELEASE` to `true`
- `src/clientversion.h`: (this mirrors `configure.ac` - see issue #3539)
    - `CLIENT_VERSION_MAJOR`
    - `CLIENT_VERSION_MINOR`
    - `CLIENT_VERSION_REVISION`
    - Don't forget to set `CLIENT_VERSION_IS_RELEASE` to `true`
- `doc/README.md` and `doc/README_windows.txt`
- `doc/Doxyfile`: `PROJECT_NUMBER` contains the full version
- `contrib/gitian-descriptors/*.yml`: usually one'd want to do this on master after branching off the release - but be sure to at least do it before a new major release
>>>>>>> pr/6

Write release notes. git shortlog helps a lot, for example:

    git shortlog --no-merges v(current version, e.g. 0.12.2)..v(new version, e.g. 0.12.3)

Generate list of authors:

    git log --format='%aN' "$*" | sort -ui | sed -e 's/^/- /'

Tag version (or release candidate) in git

    git tag -s v(new version, e.g. 0.12.3)

### Setup and perform Gitian builds

If you're using the automated script (found in [contrib/gitian-build.sh](/contrib/gitian-build.sh)), then at this point you should run it with the "--build" command. Otherwise ignore this.

<<<<<<< HEAD
	pushd ./polis
	export SIGNER=(your Gitian key, ie bluematt, sipa, etc)
	export VERSION=(new version, e.g. 0.8.0)
	git fetch
	git checkout v${VERSION}
	popd
=======
Setup Gitian descriptors:
>>>>>>> pr/6

    pushd ./dash
    export SIGNER=(your Gitian key, ie bluematt, sipa, etc)
    export VERSION=(new version, e.g. 0.12.3)
    git fetch
    git checkout v${VERSION}
    popd

Ensure your gitian.sigs are up-to-date if you wish to gverify your builds against other Gitian signatures.

    pushd ./gitian.sigs
    git pull
    popd

Ensure gitian-builder is up-to-date:

    pushd ./gitian-builder
    git pull
    popd


### Fetch and create inputs: (first time, or when dependency versions change)

    pushd ./gitian-builder
    mkdir -p inputs
    wget -P inputs https://bitcoincore.org/cfields/osslsigncode-Backports-to-1.7.1.patch
    wget -P inputs http://downloads.sourceforge.net/project/osslsigncode/osslsigncode/osslsigncode-1.7.1.tar.gz
    popd

Create the OS X SDK tarball, see the [OS X readme](README_osx.md) for details, and copy it into the inputs directory.

### Optional: Seed the Gitian sources cache and offline git repositories

By default, Gitian will fetch source files as needed. To cache them ahead of time:

<<<<<<< HEAD
	make -C ../polis/depends download SOURCES_PATH=`pwd`/cache/common
=======
    pushd ./gitian-builder
    make -C ../dash/depends download SOURCES_PATH=`pwd`/cache/common
    popd
>>>>>>> pr/6

Only missing files will be fetched, so this is safe to re-run for each build.

NOTE: Offline builds must use the --url flag to ensure Gitian fetches only from local URLs. For example:
<<<<<<< HEAD
```
./bin/gbuild --url polis=/path/to/polis,signature=/path/to/sigs {rest of arguments}
```
=======

    pushd ./gitian-builder
    ./bin/gbuild --url dash=/path/to/dash,signature=/path/to/sigs {rest of arguments}
    popd

>>>>>>> pr/6
The gbuild invocations below <b>DO NOT DO THIS</b> by default.

### Build and sign polis Core for Linux, Windows, and OS X:

<<<<<<< HEAD
	./bin/gbuild --num-make 24 --memory 64000 --commit polis=v${VERSION} ../polis/contrib/gitian-descriptors/gitian-linux.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-linux --destination ../gitian.sigs/ ../polis/contrib/gitian-descriptors/gitian-linux.yml
	mv build/out/poliscore-*.tar.gz build/out/src/poliscore-*.tar.gz ../

	./bin/gbuild --num-make 24 --memory 64000 --commit polis=v${VERSION} ../polis/contrib/gitian-descriptors/gitian-win.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-win-unsigned --destination ../gitian.sigs/ ../polis/contrib/gitian-descriptors/gitian-win.yml
	mv build/out/poliscore-*-win-unsigned.tar.gz inputs/poliscore-win-unsigned.tar.gz
	mv build/out/poliscore-*.zip build/out/poliscore-*.exe ../

	./bin/gbuild --num-make 24 --memory 64000 --commit polis=v${VERSION} ../polis/contrib/gitian-descriptors/gitian-osx.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-osx-unsigned --destination ../gitian.sigs/ ../polis/contrib/gitian-descriptors/gitian-osx.yml
	mv build/out/polis-*-osx-unsigned.tar.gz inputs/polis-osx-unsigned.tar.gz
	mv build/out/polis-*.tar.gz build/out/polis-*.dmg ../
=======
    pushd ./gitian-builder
    ./bin/gbuild --memory 3000 --commit dash=v${VERSION} ../dash/contrib/gitian-descriptors/gitian-linux.yml
    ./bin/gsign --signer $SIGNER --release ${VERSION}-linux --destination ../gitian.sigs/ ../dash/contrib/gitian-descriptors/gitian-linux.yml
    mv build/out/dash-*.tar.gz build/out/src/dash-*.tar.gz ../

    ./bin/gbuild --memory 3000 --commit dash=v${VERSION} ../dash/contrib/gitian-descriptors/gitian-win.yml
    ./bin/gsign --signer $SIGNER --release ${VERSION}-win-unsigned --destination ../gitian.sigs/ ../dash/contrib/gitian-descriptors/gitian-win.yml
    mv build/out/dash-*-win-unsigned.tar.gz inputs/dash-win-unsigned.tar.gz
    mv build/out/dash-*.zip build/out/dash-*.exe ../

    ./bin/gbuild --memory 3000 --commit dash=v${VERSION} ../dash/contrib/gitian-descriptors/gitian-osx.yml
    ./bin/gsign --signer $SIGNER --release ${VERSION}-osx-unsigned --destination ../gitian.sigs/ ../dash/contrib/gitian-descriptors/gitian-osx.yml
    mv build/out/dash-*-osx-unsigned.tar.gz inputs/dash-osx-unsigned.tar.gz
    mv build/out/dash-*.tar.gz build/out/dash-*.dmg ../
    popd
>>>>>>> pr/6

Build output expected:

<<<<<<< HEAD
  1. source tarball (polis-${VERSION}.tar.gz)
  2. linux 32-bit and 64-bit dist tarballs (polis-${VERSION}-linux[32|64].tar.gz)
  3. windows 32-bit and 64-bit unsigned installers and dist zips (polis-${VERSION}-win[32|64]-setup-unsigned.exe, polis-${VERSION}-win[32|64].zip)
  4. OS X unsigned installer and dist tarball (polis-${VERSION}-osx-unsigned.dmg, polis-${VERSION}-osx64.tar.gz)
  5. Gitian signatures (in gitian.sigs/${VERSION}-<linux|{win,osx}-unsigned>/(your Gitian key)/

### Verify other gitian builders signatures to your own. (Optional)

  Add other gitian builders keys to your gpg keyring

	gpg --import ../polis/contrib/gitian-downloader/*.pgp
=======
  1. source tarball (`dash-${VERSION}.tar.gz`)
  2. linux 32-bit and 64-bit dist tarballs (`dash-${VERSION}-linux[32|64].tar.gz`)
  3. windows 32-bit and 64-bit unsigned installers and dist zips (`dash-${VERSION}-win[32|64]-setup-unsigned.exe`, `dash-${VERSION}-win[32|64].zip`)
  4. OS X unsigned installer and dist tarball (`dash-${VERSION}-osx-unsigned.dmg`, `dash-${VERSION}-osx64.tar.gz`)
  5. Gitian signatures (in `gitian.sigs/${VERSION}-<linux|{win,osx}-unsigned>/(your Gitian key)/`)

### Verify other gitian builders signatures to your own. (Optional)

Add other gitian builders keys to your gpg keyring, and/or refresh keys.
>>>>>>> pr/6

    gpg --import dash/contrib/gitian-keys/*.pgp
    gpg --refresh-keys

<<<<<<< HEAD
	./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-linux ../polis/contrib/gitian-descriptors/gitian-linux.yml
	./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-win-unsigned ../polis/contrib/gitian-descriptors/gitian-win.yml
	./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-osx-unsigned ../polis/contrib/gitian-descriptors/gitian-osx.yml
=======
Verify the signatures
>>>>>>> pr/6

    pushd ./gitian-builder
    ./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-linux ../dash/contrib/gitian-descriptors/gitian-linux.yml
    ./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-win-unsigned ../dash/contrib/gitian-descriptors/gitian-win.yml
    ./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-osx-unsigned ../dash/contrib/gitian-descriptors/gitian-osx.yml
    popd

### Next steps:

Commit your signature to gitian.sigs:

<<<<<<< HEAD
	pushd gitian.sigs
	git add ${VERSION}-linux/${SIGNER}
	git add ${VERSION}-win-unsigned/${SIGNER}
	git add ${VERSION}-osx-unsigned/${SIGNER}
	git commit -a
	git push  # Assuming you can push to the gitian.sigs tree
	popd

  Wait for Windows/OS X detached signatures:
	Once the Windows/OS X builds each have 3 matching signatures, they will be signed with their respective release keys.
	Detached signatures will then be committed to the [polis-detached-sigs](https://github.com/polispay/polis-detached-sigs) repository, which can be combined with the unsigned apps to create signed binaries.

  Create (and optionally verify) the signed OS X binary:

	pushd ./gitian-builder
	./bin/gbuild -i --commit signature=v${VERSION} ../polis/contrib/gitian-descriptors/gitian-osx-signer.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-osx-signed --destination ../gitian.sigs/ ../polis/contrib/gitian-descriptors/gitian-osx-signer.yml
	./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-osx-signed ../polis/contrib/gitian-descriptors/gitian-osx-signer.yml
	mv build/out/polis-osx-signed.dmg ../polis-${VERSION}-osx.dmg
	popd

  Create (and optionally verify) the signed Windows binaries:

	pushd ./gitian-builder
	./bin/gbuild -i --commit signature=v${VERSION} ../polis/contrib/gitian-descriptors/gitian-win-signer.yml
	./bin/gsign --signer $SIGNER --release ${VERSION}-win-signed --destination ../gitian.sigs/ ../polis/contrib/gitian-descriptors/gitian-win-signer.yml
	./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-win-signed ../polis/contrib/gitian-descriptors/gitian-win-signer.yml
	mv build/out/polis-*win64-setup.exe ../polis-${VERSION}-win64-setup.exe
	mv build/out/polis-*win32-setup.exe ../polis-${VERSION}-win32-setup.exe
	popd
=======
    pushd gitian.sigs
    git add ${VERSION}-linux/${SIGNER}
    git add ${VERSION}-win-unsigned/${SIGNER}
    git add ${VERSION}-osx-unsigned/${SIGNER}
    git commit -a
    git push  # Assuming you can push to the gitian.sigs tree
    popd
>>>>>>> pr/6

Wait for Windows/OS X detached signatures:

- Once the Windows/OS X builds each have 3 matching signatures, they will be signed with their respective release keys.
- Detached signatures will then be committed to the [dash-detached-sigs](https://github.com/dashpay/dash-detached-sigs) repository, which can be combined with the unsigned apps to create signed binaries.

Create (and optionally verify) the signed OS X binary:

    pushd ./gitian-builder
    ./bin/gbuild -i --commit signature=v${VERSION} ../dash/contrib/gitian-descriptors/gitian-osx-signer.yml
    ./bin/gsign --signer $SIGNER --release ${VERSION}-osx-signed --destination ../gitian.sigs/ ../dash/contrib/gitian-descriptors/gitian-osx-signer.yml
    ./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-osx-signed ../dash/contrib/gitian-descriptors/gitian-osx-signer.yml
    mv build/out/dash-osx-signed.dmg ../dash-${VERSION}-osx.dmg
    popd

Create (and optionally verify) the signed Windows binaries:

    pushd ./gitian-builder
    ./bin/gbuild -i --commit signature=v${VERSION} ../dash/contrib/gitian-descriptors/gitian-win-signer.yml
    ./bin/gsign --signer $SIGNER --release ${VERSION}-win-signed --destination ../gitian.sigs/ ../dash/contrib/gitian-descriptors/gitian-win-signer.yml
    ./bin/gverify -v -d ../gitian.sigs/ -r ${VERSION}-win-signed ../dash/contrib/gitian-descriptors/gitian-win-signer.yml
    mv build/out/dash-*win64-setup.exe ../dash-${VERSION}-win64-setup.exe
    mv build/out/dash-*win32-setup.exe ../dash-${VERSION}-win32-setup.exe
    popd

Commit your signature for the signed OS X/Windows binaries:

    pushd gitian.sigs
    git add ${VERSION}-osx-signed/${SIGNER}
    git add ${VERSION}-win-signed/${SIGNER}
    git commit -a
    git push  # Assuming you can push to the gitian.sigs tree
    popd

### After 3 or more people have gitian-built and their results match:

- Create `SHA256SUMS.asc` for the builds, and GPG-sign it:

```bash
sha256sum * > SHA256SUMS
```

The list of files should be:
```
dash-${VERSION}-aarch64-linux-gnu.tar.gz
dash-${VERSION}-arm-linux-gnueabihf.tar.gz
dash-${VERSION}-i686-pc-linux-gnu.tar.gz
dash-${VERSION}-x86_64-linux-gnu.tar.gz
dash-${VERSION}-osx64.tar.gz
dash-${VERSION}-osx.dmg
dash-${VERSION}.tar.gz
dash-${VERSION}-win32-setup.exe
dash-${VERSION}-win32.zip
dash-${VERSION}-win64-setup.exe
dash-${VERSION}-win64.zip
```
The `*-debug*` files generated by the gitian build contain debug symbols
for troubleshooting by developers. It is assumed that anyone that is interested
in debugging can run gitian to generate the files for themselves. To avoid
end-user confusion about which file to pick, as well as save storage
space *do not upload these to the dash.org server*.

- GPG-sign it, delete the unsigned file:
```
gpg --digest-algo sha256 --clearsign SHA256SUMS # outputs SHA256SUMS.asc
rm SHA256SUMS
```
(the digest algorithm is forced to sha256 to avoid confusion of the `Hash:` header that GPG adds with the SHA256 used for the files)
Note: check that SHA256SUMS itself doesn't end up in SHA256SUMS, which is a spurious/nonsensical entry.

- Upload zips and installers, as well as `SHA256SUMS.asc` from last step, to the polis.org server

- Update polis.org

- Announce the release:

  - Release on polis forum: https://www.polis.org/forum/topic/official-announcements.54/

<<<<<<< HEAD
  - polis-development mailing list

  - Update title of #polispay on Freenode IRC

  - Optionally reddit /r/polispay, ... but this will usually sort out itself

- Notify flare so that he can start building [the PPAs](https://launchpad.net/~polis.org/+archive/ubuntu/polis)
=======
  - Optionally Discord, twitter, reddit /r/Dashpay, ... but this will usually sort out itself

  - Notify flare so that he can start building [the PPAs](https://launchpad.net/~dash.org/+archive/ubuntu/dash)

  - Archive release notes for the new version to `doc/release-notes/` (branch `master` and branch of the release)
>>>>>>> pr/6

  - Create a [new GitHub release](https://github.com/dashpay/dash/releases/new) with a link to the archived release notes.

  - Celebrate
