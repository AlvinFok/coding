import {Wafer} from './Wafer';
import {Subrecipe} from './Subrecipe';
import {ProcessTool} from './ProcessTool';
import {Adapter} from './Adapter';
import {Adapter_A} from './Adapter';
import {Adapter_B} from './Adapter';
import {CreateSubrecipeModeFactory} from './CreateSubrecipeModeFactory';
import {ByProductStrategyFactory} from './CreateSubrecipeModeFactory';
import {ByRecommandFactory} from './CreateSubrecipeModeFactory';
import {ByFeedforwardFactory} from './CreateSubrecipeModeFactory';

export class APC{
		
		public adapter: Adapter;
		public subrecipeFactory: CreateSubrecipeModeFactory;
		
		public genSubrecipe(wafer: Wafer): Subrecipe
		{
				if(wafer.genSubrecipeMode == 'ByProductStrategy'){
						this.subrecipeFactory = new ByProductStrategyFactory();
				}else if(wafer.genSubrecipeMode == 'Recommend'){
						this.subrecipeFactory = new ByRecommandFactory();
				}else{
						this.subrecipeFactory = new ByFeedforwardFactory();
				}
				
				return this.subrecipeFactory.genCreateMode().genSubrecipe(wafer);	
		}			
		
		public execute(wafer: Wafer, processTool: ProcessTool): void
		{				
				var sr = this.genSubrecipe(wafer);
				
				if(processTool.toolName == 'A'){
						this.adapter = new Adapter_A(processTool);
				}else if(processTool.toolName == 'B'){
						this.adapter = new Adapter_B(processTool);
				}else{
						// default tool A
						this.adapter = new Adapter_A(processTool);
				}
				
				this.adapter.execute(sr);
		}
}