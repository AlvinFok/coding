import {Subrecipe} from './Subrecipe';

export class ProcessTool{
		public toolName: string;
		
		constructor(toolName: string){
				this.toolName = toolName;
		};				
		
		public execute(sr: Subrecipe): void
		{
				console.log('Process Tool '+ this.toolName +' execute subrecipe[ '+ sr.name +' ]');
		};
}
