#!/usr/bin/env bash
# Reproduces the buggyHAL archival cleanup on a fresh clone.
# Drop README.md, LICENSE and .gitignore into the repo root first, then run this
# from the repo root on the branch you want the commit on.
set -euo pipefail

test -f README.md && test -f LICENSE && test -f .gitignore || {
  echo "Place README.md, LICENSE and .gitignore in the repo root first." >&2; exit 1; }

git rm -r --quiet Debug Release
git rm -r --quiet Core/Inc/Backup Core/Src/Backup
mkdir -p docs
git mv API_Doc_Group27.txt docs/API_Doc_Group27.txt
git mv "buggy_Using_HAL Debug (1).cfg" buggy_Using_HAL_Debug.cfg
git rm --quiet "buggy_Using_HAL Debug (1).launch" "buggy_Using_HAL Debug (2).launch"
git add -A

git commit -F - <<'MSG'
Prepare repository for archival: docs, licence, and cleanup

This project is no longer maintained. Tidy the repository so it reads
well as an archived reference.

Documentation:
- Add README.md covering the system architecture, pin/peripheral map,
  control flow, build and flashing instructions, and an explicit
  project-status section recording which subsystems were completed,
  which were configured but never activated (line sensing, steering,
  CONSTANT_SPEED state, BLE protocol), and the known issues left in
  the code.
- Add MIT LICENSE, noting that Drivers/ remains under ST's own terms.

Repository cleanup:
- Stop tracking the IDE build trees (Debug/, Release/) and the
  STM32CubeIDE .bak Backup/ directories; add a .gitignore covering
  build output, CubeMX backups, Eclipse state, and OS cruft.
- Rename "buggy_Using_HAL Debug (1).cfg" to buggy_Using_HAL_Debug.cfg.
- Remove the two byte-identical duplicate launch configurations,
  keeping "buggy_Using_HAL Debug.launch".
- Move API_Doc_Group27.txt into docs/.
MSG

echo "Done. Review with: git show --stat HEAD"
