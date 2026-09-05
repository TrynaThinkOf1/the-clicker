if [ ! "$(eval pwd | awk -F'/' '{print $NF}')" = "the-clicker" ]; then
  echo "[ERROR] Current working directory for running this script must be the root repo directory!"
  exit 1
fi

if [ -f clicker ]; then
  mkdir -p dmg_content/clicker.app/Contents/{MacOS,Resources} # Create the actual app bundle holder

  cp app_bundling/Info.plist dmg_content/clicker.app/Contents/
  cp app_bundling/icon.icns dmg_content/clicker.app/Contents/Resources/AppIcon.icns

  cp clicker dmg_content/clicker.app/Contents/MacOS/

  # link the gtk/glib/pango/cairo dylibs to the binary
  dylibbundler -od -b -x dmg_content/clicker.app/Contents/MacOS/clicker \
  -d dmg_content/clicker.app/Contents/Frameworks \
  -p @executable_path/../Frameworks
else
  echo "[ERROR] No ``clicker`` binary found!"
fi