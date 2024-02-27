import {Wafer} from './Wafer';
import {Subrecipe} from './Subrecipe';
import {ProcessTool} from './ProcessTool';
import {Adapter} from './Adapter';
import {Adapter_A} from './Adapter';
import {Adapter_B} from './Adapter';
import {Adapter_C} from './Adapter';

export class APC{
		
		public adapter: Adapter;
		
		public genSubrecipe(wafer: Wafer): Subrecipe
		{
				return new Subrecipe('APC Subrecipe for '+ wafer.id);
		}
		
		public execute(wafer: Wafer, processTool: ProcessTool): void
		{				
				var sr = this.genSubrecipe(wafer);
				
				if(processTool.toolName == 'A'){
						this.adapter = new Adapter_A(processTool);
				}else if(processTool.toolName == 'B'){
						this.adapter = new Adapter_B(processTool);
				}
				else if(processTool.toolName == 'C'){
					this.adapter = new Adapter_C(processTool);
				}
				else{
						// default tool A
						this.adapter = new Adapter_A(processTool);
				}
				
				this.adapter.execute(sr);
		}
}