import {Wafer} from './Wafer';
import {Subrecipe} from './Subrecipe';
import {ProcessTool} from './ProcessTool';
import {Adapter} from './Adapter';
import {Adapter_A} from './Adapter';
import {Adapter_B} from './Adapter';
import {ProductStrategy} from './ProductStrategy';
import {MPStrategy} from './ProductStrategy';
import {PCStrategy} from './ProductStrategy';
import {NBStrategy} from './ProductStrategy';

export class APC{
		
		public adapter: Adapter;
		public productStrategy : ProductStrategy;
		
		public genSubrecipe(wafer: Wafer): Subrecipe
		{
				this.productStrategy = this.decideProductStrategy(wafer);				
				return this.productStrategy.genSubrecipe(wafer);
		}
		
		private decideProductStrategy(wafer: Wafer): ProductStrategy
		{
				if(wafer.product == 'Mobile Phone'){
						return new MPStrategy();
				}else if(wafer.product == 'Personal Computer'){
						return new PCStrategy();
				}else{
						return new NBStrategy();
				}					
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