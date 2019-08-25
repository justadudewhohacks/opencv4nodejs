var worldModule = 'world';
function getLibsFactory(args) {
    var opencvModules = args.opencvModules, isWin = args.isWin, isOSX = args.isOSX, fs = args.fs, path = args.path;
    function getLibPrefix() {
        return isWin() ? 'opencv_' : 'libopencv_';
    }
    function getLibSuffix() {
        return isWin() ? 'lib' : (isOSX() ? 'dylib' : 'so');
    }
    function getLibNameRegex(opencvModuleName) {
        return new RegExp("^" + getLibPrefix() + opencvModuleName + "[0-9]{0,3}." + getLibSuffix() + "$");
    }
    function createLibResolver(libDir) {
        function getLibAbsPath(libFile) {
            return (libFile
                ? fs.realpathSync(path.resolve(libDir, libFile))
                : undefined);
        }
        function matchLibName(libFile, opencvModuleName) {
            return !!(libFile.match(getLibNameRegex(opencvModuleName)) || [])[0];
        }
        var libFiles = fs.readdirSync(libDir);
        return function (opencvModuleName) {
            return getLibAbsPath(libFiles.find(function (libFile) { return matchLibName(libFile, opencvModuleName); }));
        };
    }
    return function (libDir) {
        if (!fs.existsSync(libDir)) {
            throw new Error("specified lib dir does not exist: " + libDir);
        }
        var resolveLib = createLibResolver(libDir);
        var worldLibPath = resolveLib(worldModule);
        if (worldLibPath) {
            return [{
                    opencvModule: worldModule,
                    libPath: worldLibPath
                }];
        }
        return opencvModules.map(function (opencvModule) { return ({
            opencvModule: opencvModule,
            libPath: resolveLib(opencvModule)
        }); });
    };
}
exports.getLibsFactory = getLibsFactory;