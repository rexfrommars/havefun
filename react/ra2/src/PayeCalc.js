import React, {Component} from 'react'

function PayeInput(props) {
	return (
		<div>
		<input type="number" value={props.in_income} onChange={props.onIncomeChange}/>

		<button type="button" onClick={props.doCalculate}>Calculate</button>
		<br/>
		<input type="checkbox"
				id="KiwiSaverBox" value="KiwiSaver"
				onChange={props.onKiwiSaverChange}
			/>
		<label htmlFor="KiwiSaverBox">KiwiSaver</label>
		<br/>
		<input type="checkbox"
				id="StudentLoanBox" value="StudnetLoan"
				onChange={props.onStudentLoanChange}
			/>
		<label htmlFor="StudentLoanBox">Student Loan</label>
		</div>
	)
}

function PayeSetting(props) {
	return (
		<div>
			{props.se_hours_per_week} <br/>
			{props.se_kiwi_saver_rate} <br/>
			{props.se_adv_thres_hourly} <br/>
			{props.se_adv_thres_weekly} <br/>
			{props.se_acc_rate} <br/>
			{props.se_acc_cap} <br/>
		</div>
	)
}

class PayeResult extends Component {
	render() {
		return (
			<p> results </p>
		)
	}
}


const DEFAULT_HOURS_PER_WEEK = 40
const DEFAULT_ACC_RATE = 1.39
const DEFAULT_ACC_CAP = 126286
const DEFAULT_KIWISAVER_RATE = 3
const DEFAULT_STUDENTLOAN_RATE = 12
const DEFAULT_STUDENTLOAN_THRES = 19448
const DEFAULT_INCOME_THRES_HOURLY = 250
const DEFAULT_INCOME_THRES_WEEKLY = 5000


class PayeCalc extends Component {
	constructor(props) {
		super(props);
		this.state = {
			in_income: "",
			in_kiwisaver: false,
			in_studentloan: false,

			se_hours_per_week: DEFAULT_HOURS_PER_WEEK,
			se_acc_rate: DEFAULT_ACC_RATE,
			se_acc_cap: DEFAULT_ACC_CAP,
			se_kiwi_saver_rate: DEFAULT_KIWISAVER_RATE,
			se_studentloan_rate: DEFAULT_STUDENTLOAN_RATE,
			se_studentloan_thres: DEFAULT_STUDENTLOAN_THRES,
			se_adv_thres_hourly: DEFAULT_INCOME_THRES_HOURLY,
			se_adv_thres_weekly: DEFAULT_INCOME_THRES_WEEKLY,
		}
		this.history = []
	}

	onIncomeChange = (e) => {
		console.log('onIncomeChange')
		console.log(e.target)
		console.log(e.target.value)
		console.log(this.history)
		this.setState({
			in_income: e.target.value
		})
	}

	onKiwiSaverChange = (v) => {
		console.log('onKiwiSaverChange')
		this.setState({
			in_kiwisaver: !this.state.in_kiwisaver,
			se_kiwi_saver_rate: DEFAULT_KIWISAVER_RATE,
		})
	}

	onStudentLoanChange = (e) => {
		console.log('onStudentLoanChange')
		this.setState({in_studentloan: !this.state.in_studentloan})
	}

	doCalculate = () => {
		console.log('doCalculate')
	}

	doResetAcc() {
		console.log('doResetAcc')
	}

	render() {
		return (
			<div>
			<h1> hello! </h1>
			<hr/>
			<PayeInput
					in_income={this.state.in_income}
					in_kiwisaver={this.state.in_kiwisaver}
					in_studentloan={this.state.in_studentloan}
					onIncomeChange={this.onIncomeChange}
					onKiwiSaverChange={this.onKiwiSaverChange}
					onStudentLoanChange={this.onStudentLoanChange}
					doCalculate={this.doCalculate}
					
				/>
			<hr/>
			<PayeSetting {...this.state}
				/>
			<hr/>
			<PayeResult {...this.state} />
			</div>
		)
	}
}

export default PayeCalc
