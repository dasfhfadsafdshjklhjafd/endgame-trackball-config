#include <zephyr/init.h>
#include <zephyr/logging/log.h>
#include <zephyr/settings/settings.h>

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static int efog_settings_wipe_init(const struct device *dev) {
	ARG_UNUSED(dev);

	int err = settings_subsys_init();
	if (err == -EALREADY) {
		err = 0;
	}
	if (err != 0) {
		LOG_ERR("Settings init failed (%d)", err);
		return err;
	}

	err = settings_delete("p2sm_sens");
	if (err == -ENOENT) {
		LOG_INF("No stored mixer settings found; nothing to wipe");
		return 0;
	}

	if (err != 0) {
		LOG_ERR("Failed to delete stored mixer settings (%d)", err);
		return err;
	}

	LOG_INF("Stored mixer settings removed on boot");
	return 0;
}

SYS_INIT(efog_settings_wipe_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
