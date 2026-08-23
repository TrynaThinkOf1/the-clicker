if [ ! "$(eval pwd | awk -F'/' '{print $NF}')" = "the-clicker" ]; then
  echo "[ERROR] Current working directory for running this script must be the root repo directory!"
  exit 1
fi

if [ -f clicker ]; then
  mkdir -p clicker.app/Contents/{MacOS,Resources} # Create the actual app bundle holder

  cp macos_app_bundling/Info.plist clicker.app/Contents/
  cp macos_app_bundling/icon.icns clicker.app/Contents/Resources/AppIcon.icns

  cp clicker clicker.app/Contents/MacOS/
else
  echo "[ERROR] No ``clicker`` binary found!"
fi