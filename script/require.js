function resolve(root, reactive) {
  root = root.replace(/\\/g, "/");
  reactive = reactive.replace(/\\/g, "/");
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
  if (native.exists(absolute)) {
    if (require.cache[absolute]) {
      return require.cache[absolute];
    }
    result = native.load(absolute);
  } else if (native.exists(absolute + ".js")) {
    absolute += ".js";
    if (require.cache[absolute]) {
      return require.cache[absolute];
    }
    result = native.load(absolute);
  } else if (native.exists(resolve(absolute, "index.js"))) {
    absolute = resolve(absolute, "index.js");
    if (require.cache[absolute]) {
      return require.cache[absolute];
    }
    result = native.load(absolute);
  } else {
    if (require.cache[name]) {
      return require.cache[name];
    } else {
      result = native.loadModule(name);
      absolute = name;
    }
  }
  if (result === undefined) {
    throw new ReferenceError("cannot load module:" + name);
  }
  require.cache[absolute] = result;
  module = current;
  exports = module.exports;
  return result;
}
require.cache = {};
module = { exports: {} };
exports = module.exports;
