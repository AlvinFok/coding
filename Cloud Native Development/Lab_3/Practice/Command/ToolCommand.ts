import {Subrecipe} from './Subrecipe';

export interface ToolCommand{
		execute(): void
}

export class ScannerJob implements ToolCommand{
		public subrecipe: Subrecipe;
		public toolName: string;
		
		constructor(subrecipe: Subrecipe, toolName: string){
				this.subrecipe = subrecipe;
				this.toolName = toolName;
		}
		
		public execute(): void
		{
				console.log('Execute ScannerJob for tool[', this.toolName, '] subrecipe[', this.subrecipe.name, ']');
		}
}

export class ReticleJob implements ToolCommand{		
		public action: string;
		
		constructor(action: string){
				this.action = action;				
		}
		
		public execute(): void
		{
				console.log('Execute ReticleJob ', this.action);
		}
}