use mpi::topology::{Communicator, SimpleCommunicator};
use clap::Parser;
use mpi::point_to_point::{Destination, Source};

#[derive(Parser, Debug)]
struct Args {
    /// Number of times to greet
    #[arg(short, long)]
    id: String,
}

fn main() {
    let id = Args::parse().id;
    println!("Hello from client {}!", &id);

    let universe = mpi::initialize().unwrap();
    let world = universe.world();

    no_comm(&id, &world);
    ping_pong(&id, &world);
}

fn no_comm(id: &String, world: &SimpleCommunicator) {
    println!(
        "Client {} rank {} of {}!",
        id,
        world.rank(),
        world.size()
    );
}

fn ping_pong(id: &String, world: &SimpleCommunicator) {
    let mut received = 0u8;
    mpi::request::scope(|scope| {
        world.process_at_rank(0).receive_into(&mut received);
        println!("[Client {}, rank {}] Received message from Server: {}", id, world.rank(), received);

        let req = world.process_at_rank(0).immediate_send(scope, &received);
        println!("[Client {}, rank {}] Sent message back to Server", id, world.rank());
        req.wait();
    });

}