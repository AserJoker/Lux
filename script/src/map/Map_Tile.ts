export class Map_Tile {
  private _name: string = "";
  private _sprite: Sprite;
  private _tags: number[] = [];
  public draw(x: number, y: number, index: number) {
    this._sprite.setSourceRect(index * 32, 0, 32, 32);
    this._sprite.setTargetRect(x, y, 32, 32);
    this._sprite.draw();
  }
  public getName() {
    return this._name;
  }
  public constructor(token: string) {
    const tileString = asset(token, "string");
    if (!tileString) {
      throw new Error("unknown tile: " + token);
    }
    const tile = JSON.parse(tileString);
    this._sprite = Sprite_load(tile.texture);
    this._sprite.setVisible(true);
    this._tags = tile.tags;
    this._name = tile.name;
  }
  public getTag(index: number) {
    this._tags[index];
  }
  public dispose() {
    this._sprite.dispose();
  }
}
