let sprite: number = 0;
let angle = 0;
const start = () => {
    _system_event_bus.listen("lux::system::Application.ready", () => {
        sprite = Sprite_load("texture::demo");
        Sprite_setTargetRect(sprite,100,100,64,64);
        Sprite_setVisible(sprite,true);
    });
    _system_event_bus.listen("lux::system::Graphic.loop", () => {
        Sprite_setRotation(sprite,16,16,angle);
        Sprite_draw(sprite);
        angle+=0.1;
        if(angle>360){
            angle = 0;
        }
    });
}
export { start };