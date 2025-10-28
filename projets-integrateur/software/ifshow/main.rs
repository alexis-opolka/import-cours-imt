
use clap::{Parser};
use ifshow;

// The arguments of the script
#[derive(Parser, Debug)]
/// A quick command-line util to show L3 interfaces properties
pub struct Input {
    /// Retrieves only the L3 properties of a specific interface identifier
    #[arg(long, short='i')]
    pub interface: Option<String>,

    /// Retrieves the L3 properties of all known interfaces by the system
    #[arg(long, short='a')]
    pub all: bool
}

fn main() {
    let args = Input::parse();

    ifshow::main(args.interface, args.all);
}
