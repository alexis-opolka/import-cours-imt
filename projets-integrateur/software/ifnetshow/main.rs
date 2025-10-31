
use clap::{Parser, Subcommand, Args};
use ifnetshow;

// The arguments of the script
#[derive(Parser, Debug)]
/// A quick command-line util to show L3 interfaces properties
pub struct Input {
    /// Retrieves only the L3 properties of a specific interface identifier
    #[arg(long, short='i')]
    pub interface: Option<String>,

    /// Retrieves the L3 properties of all known interfaces by the system
    #[arg(long, short='a')]
    pub all: bool,

    /// Sends the request to given IP
    #[arg(long, short='n')]
    pub netaddr: Option<String>,

    /// Generates the server instance of inetshow
    #[clap(subcommand)]
    server: ServerCommands
}

#[derive(Debug, Clone, Subcommand)]
pub enum ServerCommands {
    /// Commands for the server instance of inetshow
    Server(ServerStartCommandsInput)
}

#[derive(Debug, Clone, Args)]
pub struct ServerStartCommandsInput {
    #[clap(subcommand)]
    pub start: ServerStartCommands
}

#[derive(Debug, Clone, Subcommand)]
pub enum ServerStartCommands {
    Start {
        /// A port for the socket to listen on
        #[clap(short='p', long)]
        port: u32
    }
}

fn main() {
    let args = Input::parse();

    ifnetshow::main(args.netaddr, args.interface, args.all);
}
