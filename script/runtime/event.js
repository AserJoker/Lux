(function () {
  const _listeners = {};
  _on_system_event = function (type) {
    const listeners = _listeners[type];
    if (listeners) {
      for (var i = 0; i < listeners.length; i++) {
        listeners[i]();
      }
    }
  }
  _system_event_bus = {
    listen(type, callback) {
      var listeners = _listeners[type] || [];
      listeners.push(callback);
      _listeners[type] = listeners;
      return function () {
        _system_event_bus.remove(type, callback);
      };
    },
    remove(type, callback) {
      var listeners = _listeners[type];
      if (listeners && listeners.length) {
        for (var i = 0; i < listeners.length; i++) {
          if (listeners[i] === callback) {
            listeners.splice(i, 1);
            return;
          }
        }
      }
    },
  };
})();
