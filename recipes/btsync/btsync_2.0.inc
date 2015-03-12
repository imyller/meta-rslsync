DESCRIPTION = "BitTorrent Sync is a simple tool that applies p2p protocol for direct live folder sync with maximum security, network speed and storage capacity"
SECTION = "network"

LICENSE = "Proprietary"

INC_PR = "r2"

PR = "${INC_PR}.0"

FILESEXTRAPATHS_prepend := "${THISDIR}/common:"

S = "${WORKDIR}"

SRC_URI = " \
        http://syncapp.bittorrent.com/${PV}/btsync_${TARGET_ARCH}-${PV}.tar.gz\
	file://btsync.conf\
	file://btsync.init\
"

INSANE_SKIP_${PN} += "ldflags"
INSANE_SKIP_${PN} += "already-stripped"

inherit update-rc.d

INITSCRIPT_NAME = "btsync"
INITSCRIPT_PARAMS = "defaults"

do_install() {
	
	install -d ${D}${sbindir}
	install -m 0755 ${WORKDIR}/btsync ${D}${sbindir}/

	install -d ${D}${localstatedir}/lib/btsync

	install -d ${D}install -d ${D}${sysconfdir}/init.d
        install -m 0755 ${WORKDIR}/btsync.init ${D}${sysconfdir}/init.d/btsync

	install -d ${D}${sysconfdir}/btsync
	install -m 0655 ${WORKDIR}/btsync.conf ${D}${sysconfdir}/btsync/

	if [ "${TARGET_ARCH}" = "arm" ]; then

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
