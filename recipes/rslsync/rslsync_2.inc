DESCRIPTION = "Resilio Sync is a simple tool that applies P2P protocol for direct live folder sync with maximum security, network speed and storage capacity"
SECTION = "network"

LICENSE = "Proprietary"

INC_PR = "r1"

PR = "${INC_PR}.0"

FILESEXTRAPATHS_prepend := "${THISDIR}/common:"

S = "${WORKDIR}"

BIN_ARCH = "${TARGET_ARCH}"
BIN_ARCH_x86_64 = "x64"
BIN_ARCH_i486 = "i386"
BIN_ARCH_i586 = "i386"
BIN_ARCH_i686 = "i386"
BIN_ARCH_armeb = "arm"
BIN_ARCH_arm = "${@bb.utils.contains('TUNE_FEATURES', 'callconvention-hard', 'armhf', 'arm', d)}"

SRC_URI = " \
        https://download-cdn.resilio.com/${PV}/linux-armhf/resilio-sync_armhf.tar.gz;name=bin_armhf;subdir=armhf;downloadfilename=${PN}-${PV}-armhf.tar.gz \
	https://download-cdn.resilio.com/${PV}/linux-arm/resilio-sync_arm.tar.gz;name=bin_arm;subdir=arm;downloadfilename=${PN}-${PV}-arm.tar.gz \
	https://download-cdn.resilio.com/${PV}/linux-x64/resilio-sync_x64.tar.gz;name=bin_x64;subdir=x64;downloadfilename=${PN}-${PV}-x64.tar.gz \
	https://download-cdn.resilio.com/${PV}/linux-i386/resilio-sync_i386.tar.gz;name=bin_i386;subdir=i386;downloadfilename=${PN}-${PV}-i386.tar.gz \
	file://rslsync.conf;name=conf \
	file://rslsync.init;name=init \
"

do_configure[noexec] = "1"
do_compile[noexec] = "1"

INSANE_SKIP_${PN} += "ldflags"
INSANE_SKIP_${PN} += "already-stripped"
INSANE_SKIP_${PN} += "file-rdeps"
INSANE_SKIP_${PN} += "build-deps"

inherit update-rc.d

INITSCRIPT_NAME = "rslsync"
INITSCRIPT_PARAMS = "defaults"

do_install() {
	install -d ${D}${sbindir}
	install -m 0755 ${WORKDIR}/${BIN_ARCH}/rslsync ${D}${sbindir}/

	install -d ${D}${localstatedir}/lib/rslsync

	install -d ${D}install -d ${D}${sysconfdir}/init.d
        install -m 0755 ${WORKDIR}/rslsync.init ${D}${sysconfdir}/init.d/rslsync

	install -d ${D}${sysconfdir}/rslsync
	install -m 0655 ${WORKDIR}/rslsync.conf ${D}${sysconfdir}/rslsync/

	if [ "${BIN_ARCH}" = "armhf" ]; then

		# Hack to fix missing ld-linux.so.3 symlink in /lib
		# Warning: currently this is not generic as it symlinks with armhf lib 
		install -d ${D}/${base_libdir}	
		ln -sf ld-linux-armhf.so.3 ${D}${base_libdir}/ld-linux.so.3

	fi
  
}

FILES_${PN} = " \
	${sbindir}/rslsync \
	${sysconfdir}/rslsync/rslsync.conf \
        ${sysconfdir}/init.d/rslsync \
	${localstatedir}/lib/rslsync \
	${base_libdir}/ld-linux.so.3 \
"

CONFFILES_${PN} = " \
        ${sysconfdir}/rslsync/rslsync.conf \
"
