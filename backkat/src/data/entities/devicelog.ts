import { Entity, ObjectIdColumn, Column, ObjectID, PrimaryColumn } from 'typeorm'

export class DeviceLog {
	@Column()
	moment?: Date

	@Column()
	log!: string

	@Column()
	level!: string
}

@Entity()
export class DeviceLogs {
	@ObjectIdColumn()
	_id?: string

	@Column(type => DeviceLog)
	logs!: DeviceLog[]
}
