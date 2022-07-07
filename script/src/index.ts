let image: number = 0;
const start = () => {
    _system_event_bus.listen("lux::system::Application.ready", () => {
        image = createImage("texture::demo");
    });
    _system_event_bus.listen("lux::system::Graphic.loop", () => {
        drawImage(image, 100, 100, 0, 0, 32, 32);
    });
}
export { start };