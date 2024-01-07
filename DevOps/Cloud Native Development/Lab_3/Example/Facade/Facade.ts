import {Subsystem} from './Subsystem';
import {SubsystemA} from './Subsystem';
import {SubsystemB} from './Subsystem';
import {SubsystemC} from './Subsystem';

export class AdditionalFacade{
		public subsystemA: Subsystem;
		public subsystemC: Subsystem;		
		
		constructor(){
				this.subsystemA = new SubsystemA();
				this.subsystemC = new SubsystemC();				
		}
		
		public anotherOperation(): void
		{
				console.log('AdditionalFacade execute()');
				this.subsystemA.execute();
				this.subsystemC.execute();				
		}
}

export class Facade{
		public subsystemA: Subsystem;
		public subsystemB: Subsystem;
		public additionalFacade: AdditionalFacade;
		
		constructor(){
				this.subsystemA = new SubsystemA();
				this.subsystemB = new SubsystemB();
				this.additionalFacade = new AdditionalFacade();
		}
		
		public subsystemOperation(): void
		{
				console.log('Facde execute()');
				this.subsystemA.execute();
				this.subsystemB.execute();
				
				this.additionalFacade.anotherOperation();
		}
}