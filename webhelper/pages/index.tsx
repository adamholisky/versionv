import Head from 'next/head'

export default function Home() {
	return (
		<>
			<Head>
				<title>Version V Operating System</title>
				<meta name="description" content="vOS web helper" />
				<meta name="viewport" content="width=device-width, initial-scale=1" />
				<link rel="icon" href="/noun-web-4913192.png" />
				<link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-GLhlTQ8iRABdZLl6O3oVMWSktQOp6b7In1Zl3/Jr59b6EGGoI1aFkw7cmDA6j6gD" crossorigin="anonymous" />
				<script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.0-alpha1/dist/js/bootstrap.bundle.min.js" integrity="sha384-w76AqPfDkMBDXo30jS1Sgez6pr3x5MlQ1ZAGC+nuZB+EYdgRZgiwxhTBTkF7CXvN" crossorigin="anonymous"></script>
			</Head>
			<nav className="navbar navbar-expand-lg bg-body-tertiary">
				<div className="container-fluid">
					<a className="navbar-brand" href="#">vOS</a>
					<button className="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNavDropdown" aria-controls="navbarNavDropdown" aria-expanded="false" aria-label="Toggle navigation">
						<span className="navbar-toggler-icon"></span>
					</button>
					<div className="collapse navbar-collapse" id="navbarNavDropdown">
						<ul className="navbar-nav">
						</ul>
					</div>
				</div>
			</nav>
			<span style={{ height: 25 }}>&nbsp;</span>
			<div className="container-fluid">
				<div className="row">
					<div className="col-sm-2">
						<ul className="nav flex-column">
							<li className="nav-item">
								<a className="nav-link active" aria-current="page" href="#">Home</a>
							</li>
							<li className="nav-item">
								<a className="nav-link disabled">Logs</a>
							</li>
							<li className="nav-item">
								<a className="nav-link" href="#">Serial</a>
							</li>
							<li className="nav-item">
								<a className="nav-link" href="#">Build</a>
							</li>
							<li className="nav-item">
								<a className="nav-link" href="#">Obj Dump</a>
							</li>
							<li className="nav-item">
								<a className="nav-link" href="#">ELF Dump</a>
							</li>
						</ul>
					</div>
					<div className="col-sm-10">
						Column
					</div>
				</div>
			</div>
		</>
	)
}
