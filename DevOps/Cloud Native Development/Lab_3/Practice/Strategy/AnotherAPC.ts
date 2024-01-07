import {Wafer} from './Wafer';
import {Subrecipe} from './Subrecipe';
import {ProcessTool} from './ProcessTool';

export class AnotherAPC{						
		public genSubrecipe(wafer: Wafer): Subrecipe
		{
				if(wafer.product == 'Mobile Phone'){
						...
						...
						return new Subrecipe('APC Subrecipe for[' + wafer.id + ']: A+B*(Fn of MobilePhone)');
				}else if(wafer.product == 'Personal Computer'){
						...
						...
						return new Subrecipe('APC Subrecipe for[' + wafer.id + ']: A+B*(Fn of PersonalComputer)');
				}else{
						...
						...
						return new Subrecipe('APC Subrecipe for[' + wafer.id + ']: A+B*(Fn of NoteBook)');
				}									
		}
		
		public execute(wafer: Wafer, processTool: ProcessTool): void
		{				
				var sr = this.genSubrecipe(wafer);
				
				if(processTool.toolName == 'A'){
						...
						...
						console.log('(Adapter A process subrecipe for Tool A)');						
				}else if(processTool.toolName == 'B'){
						...
						...
						console.log('(Adapter B process subrecipe for Tool B)');				
				}else{
						// default tool A
						console.log('(Adapter A process subrecipe for Tool A)');						
				}
				
				processTool.execute(sr);
		}
}