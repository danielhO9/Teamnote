#!/usr/bin/env python3
"""Validate that KACTL imports exist with the exact same filename casing."""

from pathlib import Path
import re
import sys


ROOT = Path(__file__).resolve().parents[1]
CONTENT = ROOT / "content"
IMPORT_PATTERN = re.compile(r"\\kactlimport(?:\[[^\]]*\])?\{([^}]+)\}")


def main() -> int:
    errors: list[str] = []

    for chapter in sorted(CONTENT.glob("*/chapter.tex")):
        source = chapter.read_text(encoding="utf-8")
        for imported in IMPORT_PATTERN.findall(source):
            target = chapter.parent / imported
            if not target.is_file():
                errors.append(
                    f"{chapter.relative_to(ROOT)}: missing exact-case import {imported!r}"
                )

    if errors:
        print("\n".join(errors), file=sys.stderr)
        return 1

    print("All KACTL imports resolve with exact filename casing.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
