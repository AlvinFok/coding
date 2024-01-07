export interface Strategy{
		execute(data: string): void;
}

export class SomeStrategy implements Strategy{
		public execute(data: string): void
		{
				console.log('SomeStrategy.execute(' + data + ')');
		}
}

export class OtherStrategy implements Strategy{
		public execute(data: string): void
		{
				console.log('OtherStrategy.execute(' + data + ')');
		}
}