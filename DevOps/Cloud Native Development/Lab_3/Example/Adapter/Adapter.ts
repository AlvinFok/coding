import {Adaptee} from './Adaptee'

export interface AdapterInterface{
		method(data: string): void;
}

export class Adapter implements AdapterInterface{				
		public adaptee: Adaptee;
		
		public method(data: string): void
		{
				this.adaptee = new Adaptee();
				this.adaptee.serviceMethod(data);
		}
}