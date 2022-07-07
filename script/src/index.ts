const start = ()=>{
    _system_event_bus.listen("lux::system::Application.ready",()=>{
        console.log("app ready");
    });
    _system_event_bus.listen("lux::system::Graphic.loop",()=>{
        console.log("graphic loop");
    });
}
export {start};