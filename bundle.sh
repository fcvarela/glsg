executable=$1

if [ ! -d "${executable}.app/Contents/MacOS" ]; then
    mkdir -p "${executable}.app/Contents/MacOS"
fi

if [ ! -d "${executable}.app/Contents/Resources" ]; then
    mkdir -p "${executable}.app/Contents/Resources"
fi

if [ ! -f "${executable}.app/Contents/PkgInfo" ]; then
    echo -n "APPL????" > "${executable}.app/Contents/PkgInfo"
fi

if [ ! -f "${executable}.app/Contents/Frameworks" ]; then
    mkdir -p "${executable.app}/Contents/Frameworks"
fi

if [ ! -f "${executable}.app/Contents/Info.plist" ]; then
    cat > "${executable}.app/Contents/Info.plist" <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple Computer//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
<key>CFBundleDevelopmentRegion</key>
<string>English</string>
<key>CFBundleExecutable</key>
<string>${executable}</string>
<key>CFBundleInfoDictionaryVersion</key>
<string>6.0</string>
<key>CFBundlePackageType</key>
<string>APPL</string>
<key>CFBundleSignature</key>
<string>VAAL</string>
<key>CFBundleVersion</key>
<string>1.0</string>
<key>CFBundleShortVersionString</key>
<string>1.0</string>
<key>CFBundleIconFile</key>
<string>Icon.icns</string>
</dict>
</plist>
EOF
fi

cp -r Icon.icns ${executable}.app/Contents/Resources/Icon.icns
