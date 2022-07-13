
import { Map_Tile } from "../map/Map_Tile";

export class System_Map {
    private _tiles:Record<string,Map_Tile> = {};
    public loadTile(token:string){
        const tile = new Map_Tile(token);
        this._tiles[tile.getName()] = tile;
    }
    public draw(x:number,y:number,name:string,index:number){
        const tile = this._tiles[name];
        if(!tile){
            throw new Error(`unknown tile name: ${name}`);
        }
        tile.draw(x,y,index);
    }
} 