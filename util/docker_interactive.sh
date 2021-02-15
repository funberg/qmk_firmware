
#!/bin/sh
# NOTE: This script uses tabs for indentation

errcho() {
	echo "$@" >&2
}

if ! command -v docker >/dev/null 2>&1; then
	errcho "Error: docker not found"
	errcho "See https://docs.docker.com/install/#supported-platforms for installation instructions"
	exit 2
fi

dir=$(pwd -W 2>/dev/null) || dir=$PWD  # Use Windows path if on Windows

# Run container and build firmware
docker run --rm -it $usb_args \
	--user $(id -u):$(id -g) \
	-w /qmk_firmware \
	-v "$dir":/qmk_firmware \
	-e ALT_GET_KEYBOARDS=true \
	-e SKIP_GIT="$SKIP_GIT" \
	-e MAKEFLAGS="$MAKEFLAGS" \
	qmkfm/base_container \
	/bin/bash
