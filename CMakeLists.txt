zephyr_library()

zephyr_library_sources_ifdef(CONFIG_EFOG_SETTINGS_WIPE_ON_BOOT
	src/settings_wipe.c
)
