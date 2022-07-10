var _runtime = runtime;
function resolve(root, reactive) {
  root = root.replace(/\\/g, "/");
  reactive = reactive.replace(/\\/g, "/");
  if (reactive[0] === '/') {
    return reactive;
  }
  const rootPath = root.split("/");
  const reactivePath = reactive.split("/");
  reactivePath.forEach(function (p) {
    if (p === ".") {
      return;
    }
    if (p === "..") {
      rootPath.length--;
      return;
    }
    rootPath.push(p);
  });
  return rootPath.join("/");
}
function require(name) {
  var result;
  var absolute = resolve(__dirname, name);
  var current = module;
  var dirname = __dirname;
  var filename = __filename;
  if (_runtime.exists(absolute)) {
    if (require.cache[absolute]) {
      return require.cache[absolute];
    }
    result = _runtime.load(absolute);
  } else if (_runtime.exists(absolute + ".js")) {
    absolute += ".js";
    if (require.cache[absolute]) {
      return require.cache[absolute];
    }
    result = _runtime.load(absolute);
  } else if (_runtime.exists(resolve(absolute, "index.js"))) {
    absolute = resolve(absolute, "index.js");
    if (require.cache[absolute]) {
      return require.cache[absolute];
    }
    result = _runtime.load(absolute);
  } else {
    if (require.cache[name]) {
      return require.cache[name];
    } else {
      result = _runtime.loadModule(name);
      absolute = name;
    }
  }
  if (result === undefined) {
    throw new ReferenceError("cannot load module:" + name);
  }
  require.cache[absolute] = result;
  module = current;
  exports = module.exports;
  __dirname = dirname;
  __filename = filename;
  return result;
}
require.cache = {};
module = { exports: {} };
exports = module.exports;
