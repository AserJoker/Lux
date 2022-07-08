let sp: Sprite;
let sps: Sprite;
let direct = false;
const start = () => {
  _system_event_bus.listen("lux::system::Application.ready", () => {
    sps = Sprite_load("texture::demo");
    sps.setTargetRect(32, 32, 32, 32);
    sps.setVisible(true);
    sp = Sprite_create(100, 100, SpriteAccess.TARGET);
    sp.setVisible(true);
    Sprite_setRenderTarget(sp);
    sps.draw();
    Sprite_setRenderTarget(undefined);
    sp.setOpacity(0);
  });
  _system_event_bus.listen("lux::system::Graphic.loop", () => {
    sp.draw();
  });
};
export { start };
