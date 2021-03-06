/***
  This file is part of systemd.

  Copyright 2016 Lennart Poettering

  systemd is free software; you can redistribute it and/or modify it
  under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  systemd is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with systemd; If not, see <http://www.gnu.org/licenses/>.
***/

#include <sys/mount.h>

#include "log.h"
#include "mount-util.h"
#include "string-util.h"

static void test_mount_propagation_flags(const char *name, unsigned long f) {
        assert(mount_propagation_flags_from_string(name) == f);

        if (f != 0)
                assert_se(streq_ptr(mount_propagation_flags_to_string(f), name));
}

int main(int argc, char *argv[]) {

        log_set_max_level(LOG_DEBUG);

        test_mount_propagation_flags("shared", MS_SHARED);
        test_mount_propagation_flags("slave", MS_SLAVE);
        test_mount_propagation_flags("private", MS_PRIVATE);
        test_mount_propagation_flags(NULL, 0);
        test_mount_propagation_flags("", 0);
        test_mount_propagation_flags("xxxx", 0);

        return 0;
}
