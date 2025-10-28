
#[warn(unused_imports)]
extern crate pnet;

use clap::Error;
use pnet::datalink::{self, NetworkInterface};
use log::debug;

// Main function when called as a standalone function
pub fn main(given_inf_name: Option<String>, all: bool) -> Result<bool, Error> {
    let interfaces = datalink::interfaces();

    if all == true {
        for interface in interfaces {
            display_interface(&interface);
        }

        return Ok(true);
    } else if ! all && interfaces.is_empty() {
        eprintln!("Please see usage with \"ifshow --help\".");

        return Ok(false);
    }

    if given_inf_name.is_some() {
        let given_interface = given_inf_name.to_owned().unwrap();

        debug!("Given interface name: {:?}", given_interface);

        let wanted_interface: Option<NetworkInterface> = datalink::interfaces()
            .into_iter()
            .find(|inf_name| inf_name.name == given_interface);

        if wanted_interface.is_none() {
            eprintln!("No network interface found with the name \"{}\".", given_inf_name.unwrap());
            return Ok(false);
        }

        display_interface(&wanted_interface.unwrap());
    }

    Ok(true)
}

fn display_interface(interface: &NetworkInterface) {
    eprint!("{}\n\t", interface.name);

    let ips_size = &interface.ips.iter().count();
    let mut count = 0;

    for ip in &interface.ips {
        // We're counting each loop we're doing
        count += 1;

        let mut ipv = "";
        if ip.is_ipv4() {
            ipv = "ipv4"
        } else if ip.is_ipv6() {
            ipv = "ipv6"
        } else {
            ipv = "unknown"
        }

        eprint!("{}: {}/{}", ipv, ip.ip(), ip.prefix());

        if (count + 1).le(ips_size) {
            eprint!(", ")
        }
    }

    eprintln!();
}
