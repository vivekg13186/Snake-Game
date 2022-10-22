VERSION="0.1"
mkdir -p Snake.app/Contents/{MacOS,Resources}
cp Snake.icns Snake.app/Contents/Resources/logo.icns
cat > Snake.app/Contents/Info.plist << EOF
{
	CFBundleName = "snake";
	CFBundleDisplayName = "Snake";
	CFBundleIndentifier = "org.Snake-sre";
	CFBundleVersion = "$VERSION";
	CFBundleShortVersionString = "${VERSION%%_*}";
	CFBundleInfoDictionaryVersion = "6.0";
	CFBundlePackageType = "APPL";
	CFBundleExecutable = "snake";
	CFBundleIconFile = "logo.icns";
}
EOF


# running our app causes MacOS to put garbage on the CLI, which makes Ghidra
# think we're trying to open a project...so we'll remove that feature from the
# launcher since we can't actually access it anyway through the GUI
#sed 's/"$@"//g' Ghidra.app/Contents/MacOS/sname > ghidraRun
chmod +x snake
cp -- snake Snake.app/Contents/MacOS/snake