export class System_Camera {
  private _rc = [0, 0, 0, 0];
  public getPosition() {
    return [this._rc[0], this._rc[1]];
  }
  public setPosition(x:number,y:number){
    this._rc[0] = x;
    this._rc[1] = y;
  }
  public move(dx:number,dy:number){
    this._rc[0]+=dx;
    this._rc[1]+=dy;
  }
  public constructor() {
    const [w, h] = native.getWindowSize();
    this._rc[2] = w;
    this._rc[3] = h;
    this._rc[0] = -w / 2;
    this._rc[1] = -h / 2;
  }
  public trasformToNative(x: number, y: number) {
    return [x - this._rc[0], y - this._rc[1]];
  }
}
