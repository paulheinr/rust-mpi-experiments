use mpi::point_to_point::{Destination, Source};
use mpi::topology::{Communicator, SimpleCommunicator};

fn main() {
    println!("Hello from server!");
    let universe = mpi::initialize().unwrap();
    let world = universe.world();

    no_comm(&world);
    ping_pong(&world);
}

fn no_comm(world: &SimpleCommunicator) {

    println!(
        "Server rank {} of {}!",
        world.rank(),
        world.size()
    );
}

fn ping_pong(world: &SimpleCommunicator) {
    let size = world.size();
    let rank = world.rank();

    assert_eq!(rank, 0);
    let message = -1i32;
    mpi::request::multiple_scope((world.size() as usize)*2, |scope, reqs| {
        for i in 1..size {
            let req = world.process_at_rank(i).immediate_send(scope, &message);
            reqs.add(req);
            println!("[Server] Sent message to process {}", i);
        }

        for i in 1..size {
            let mut received = 0i32;
            world.process_at_rank(i).receive_into(&mut received);
            println!("[Server] Received message from process {}: {}", i, received);
        }

        reqs.wait_all(&mut vec![]);
    });
}