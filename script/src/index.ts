let image: number = 0;
const start = () => {
    _system_event_bus.listen("lux::system::Application.ready", () => {
        image = createImage("texture::demo");
        console.log(image, 0);
    });
    _system_event_bus.listen("lux::system::Graphic.loop", () => {
        console.log(image, 1);
        drawImage(image, 100, 100, 0, 0, 32, 32);
    });
}
export { start };