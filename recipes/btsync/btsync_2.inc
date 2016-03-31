DESCRIPTION = "BitTorrent Sync is a simple tool that applies p2p protocol for direct live folder sync with maximum security, network speed and storage capacity"
SECTION = "network"

LICENSE = "Proprietary"

INC_PR = "r6"

PR = "${INC_PR}.0"

FILESEXTRAPATHS_prepend := "${THISDIR}/common:"

S = "${WORKDIR}"

BIN_ARCH = "${TARGET_ARCH}"
BIN_ARCH_x86_64 = "x64"
BIN_ARCH_i486 = "i386"
BIN_ARCH_i586 = "i386"
BIN_ARCH_i686 = "i386"
BIN_ARCH_armeb = "arm"
BIN_ARCH_arm = "${@base_contains('TUNE_FEATURES', 'callconvention-hard', 'armhf', 'arm', d)}"

SRC_URI = " \
        https://download-cdn.getsync.com/${PV}/linux-armhf/BitTorrent-Sync_armhf.tar.gz;name=bin_armhf;subdir=armhf \
	https://download-cdn.getsync.com/${PV}/linux-arm/BitTorrent-Sync_arm.tar.gz;name=bin_arm;subdir=arm \
	https://download-cdn.getsync.com/${PV}/linux-x64/BitTorrent-Sync_x64.tar.gz;name=bin_x64;subdir=x64 \
	https://download-cdn.getsync.com/${PV}/linux-i386/BitTorrent-Sync_i386.tar.gz;name=bin_i386;subdir=i386 \
	file://btsync.conf;name=conf \
	file://btsync.init;name=init \
"

do_configure[noexec] = "1"
do_compile[noexec] = "1"

INSANE_SKIP_${PN} += "ldflags"
INSANE_SKIP_${PN} += "already-stripped"
INSANE_SKIP_${PN} += "file-rdeps"
INSANE_SKIP_${PN} += "build-deps"

inherit update-rc.d

INITSCRIPT_NAME = "btsync"
INITSCRIPT_PARAMS = "defaults"

do_install() {
	install -d ${D}${sbindir}
	install -m 0755 ${WORKDIR}/${BIN_ARCH}/btsync ${D}${sbindir}/

	install -d ${D}${localstatedir}/lib/btsync

	install -d ${D}install -d ${D}${sysconfdir}/init.d
        install -m 0755 ${WORKDIR}/btsync.init ${D}${sysconfdir}/init.d/btsync

	install -d ${D}${sysconfdir}/btsync
	install -m 0655 ${WORKDIR}/btsync.conf ${D}${sysconfdir}/btsync/

	if [ "${BIN_ARCH}" = "armhf" ]; then

		# Hack to fix missing ld-linux.so.3 symlink in /lib
		# Warning: currently this is not generic as it symlinks with armhf lib 
		install -d ${D}/${base_libdir}	
		ln -sf ld-linux-armhf.so.3 ${D}${base_libdir}/ld-linux.so.3

	fi
  
}

FILES_${PN} = " \
	${sbindir}/btsync \
	${sysconfdir}/btsync/btsync.conf \
        ${sysconfdir}/init.d/btsync \
	${localstatedir}/lib/btsync \
	${base_libdir}/ld-linux.so.3 \
"

CONFFILES_${PN} = " \
        ${sysconfdir}/btsync/btsync.conf \
"
