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
  const _tasks = [];
  var _task_id = 0;
  function _createTask(cb, delay) {
    return {
      cb, delay, id: ++_task_id, start: Date.now()
    }
  }
  setTimeout = function (cb, delay) {
    if (delay === undefined) {
      delay = 0;
    }
    const task = _createTask(cb, delay);
    _tasks.push(task);
    return task.id;
  }
  clearTimeout = function (id) {
    for (var i = 0; i < _tasks.length; i++) {
      if (_tasks[i].id === id) {
        _tasks.splice(id, 1);
        return;
      }
    }
  }
  nextTick = function (cb) {
    setTimeout(cb);
  }
  _system_event_bus.listen("lux::system::Graphic.loop", function () {
    if (_tasks.length) {
      const task = _tasks.shift();
      if (Date.now() - task.start >= task.delay) {
        task.cb();
      } else {
        _tasks.push(task);
      }
    }
  });
})();
