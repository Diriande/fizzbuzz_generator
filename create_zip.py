#!/usr/bin/env python3
"""
Utility script to create a source-only archive of the FizzBuzz project.

This is meant to satisfy the deliverable requirement:
    "Deliverable: only your sources in a .zip or .tar.gz archive!"

By default, it creates a ZIP file named "fizzbuzz_project.zip"
in the project root, containing:
  - CMakeLists.txt
  - conanfile.py
  - cliff.toml, Doxyfile, sonar-project.properties
  - all sources under src/, include/, tests/
  - .github/ (CI configuration), if present

The following are excluded:
  - build/ directories
  - any existing *.zip / *.tar.gz archives
  - typical VCS metadata (.git, .svn, etc.)
"""

import argparse
from pathlib import Path
from typing import Iterable, List
import zipfile


PROJECT_ROOT = Path(__file__).resolve().parent


EXCLUDE_DIR_NAMES = {
    "build",
    ".git",
    ".svn",
    ".idea",
    ".vscode",
    "__pycache__",
}

EXCLUDE_FILE_SUFFIXES = {
    ".zip",
    ".tar",
    ".tar.gz",
    ".tgz",
}


def should_exclude(path: Path) -> bool:
    """Return True if this path should be excluded from the archive."""
    # Exclude build / VCS / editor metadata directories
    for parent in path.parents:
        if parent.name in EXCLUDE_DIR_NAMES:
            return True

    # Exclude known archive formats
    for suffix in EXCLUDE_FILE_SUFFIXES:
        if str(path).endswith(suffix):
            return True

    return False


def iter_files_to_add(root: Path) -> Iterable[Path]:
    """Yield all files that should be added to the archive."""
    # Explicit top-level files we consider part of the "sources"
    top_level_files: List[str] = [
        "CMakeLists.txt",
        "conanfile.py",
        "cliff.toml",
        "Doxyfile",
        "sonar-project.properties",
        "README.md",
        "create_zip.py",
    ]

    for name in top_level_files:
        candidate = root / name
        if candidate.is_file() and not should_exclude(candidate):
            yield candidate

    # Source trees
    for subdir in ("src", "include", "tests", ".github"):
        base = root / subdir
        if not base.exists():
            continue

        for path in base.rglob("*"):
            if path.is_file() and not should_exclude(path):
                yield path


def create_zip(output: Path) -> None:
    """Create a ZIP archive with all relevant source files."""
    # Ensure we don't accidentally include the archive we are writing
    if output.exists():
        output.unlink()

    with zipfile.ZipFile(output, "w", compression=zipfile.ZIP_DEFLATED) as zf:
        for file_path in iter_files_to_add(PROJECT_ROOT):
            # Store paths relative to the project root
            arcname = file_path.relative_to(PROJECT_ROOT)
            zf.write(file_path, arcname)
            print(f"Added: {arcname}")

    print(f"\nCreated archive: {output}")


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Create a source-only ZIP archive of the FizzBuzz project."
    )
    parser.add_argument(
        "-o",
        "--output",
        type=str,
        default="fizzbuzz_project.zip",
        help="Name of the output archive (default: fizzbuzz_project.zip)",
    )

    args = parser.parse_args()
    output_path = (PROJECT_ROOT / args.output).resolve()

    create_zip(output_path)


if __name__ == "__main__":
    main()
