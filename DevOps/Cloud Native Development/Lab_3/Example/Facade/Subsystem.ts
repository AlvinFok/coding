export interface Subsystem{
		execute(): void;
}

export class SubsystemA implements Subsystem{
		public execute():void
		{
				console.log('Subsystem A execute()');
		}
}

export class SubsystemB implements Subsystem{
		public execute():void
		{
				console.log('Subsystem B execute()');
		}
}

export class SubsystemC implements Subsystem{
		public execute():void
		{
				console.log('Subsystem C execute()');
		}
}